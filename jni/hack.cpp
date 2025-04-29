#include "hack.h"

bool isAutoPlayFlorentino;
bool AimSkill;

void (*_LActorRoot_Visible)(...);
void LActorRoot_Visible(void *instance, int camp, bool bVisible, const bool forceSync = false) {
    if (instance != nullptr) {
        if (camp == 1 || camp == 2 || camp == 110 || camp == 255) {
            bVisible = true;
        }
    }
    return _LActorRoot_Visible(instance, camp, bVisible, forceSync);
}

struct EntityInfo {
    Vector3 myPos;
    Vector3 enemyPos;
    Vector3 moveForward;
    int ConfigID;
    bool isMoving;
    int myObjCamp;
};

EntityInfo EnemyTarget;

Vector3 RotateVectorByQuaternion(Quaternion q) {
    Vector3 v(0.0f, 0.0f, 1.0f);
    float w = q.w, x = q.x, y = q.y, z = q.z;

    Vector3 u(x, y, z);
    Vector3 cross1 = Vector3::Cross(u, v);
    Vector3 cross2 = Vector3::Cross(u, cross1);
    Vector3 result = v + 2.0f * cross1 * w + 2.0f * cross2;

    return result;
}

float SquaredDistance(Vector3 v, Vector3 o) {
    return (v.x - o.x) * (v.x - o.x) + (v.y - o.y) * (v.y - o.y) + (v.z - o.z) * (v.z - o.z);
}

Vector3 calculateSkillDirection(Vector3 myPosi, Vector3 enemyPosi, bool isMoving, Vector3 moveForward) {
    if (isMoving) { enemyPosi += moveForward; }
    Vector3 direction = enemyPosi - myPosi;
    direction.Normalize();
    return direction;
}

bool isCharging;
int mode = 0, aimType = 1, drawType = 2, skillSlot;

Vector3 (*_GetUseSkillDirection)(void *instance, bool isTouchUse);
Vector3 GetUseSkillDirection(void *instance, bool isTouchUse) {
    if (instance != NULL && AimSkill && EnemyTarget.ConfigID == 196) {
        if (EnemyTarget.myPos != Vector3::zero() && EnemyTarget.enemyPos != Vector3::zero() && skillSlot == 2) {
            return calculateSkillDirection(EnemyTarget.myPos, EnemyTarget.enemyPos, EnemyTarget.isMoving, EnemyTarget.moveForward);
        }
    }
    return _GetUseSkillDirection(instance, isTouchUse);
}

uintptr_t m_isCharging, m_currentSkillSlotType;
void (*_UpdateLogic)(void *instance, int delta);
void UpdateLogic(void *instance, int delta) {
    if (instance != NULL) {
        isCharging = *(bool *)((uintptr_t)instance + 0x56);
        skillSlot = *(int *)((uintptr_t)instance + 0x2C);
    }

    Quaternion rotation;
    float minDistance = std::numeric_limits<float>::infinity();
    float minDirection = std::numeric_limits<float>::infinity();
    float minHealth = std::numeric_limits<float>::infinity();
    float minHealth2 = std::numeric_limits<float>::infinity();
    float minHealthPercent = std::numeric_limits<float>::infinity();
    ActorLinker *Entity = nullptr;

    ActorManager *get_actorManager = KyriosFramework::get_actorManager();
    if (get_actorManager == nullptr) return;

    List<ActorLinker *> *GetAllHeros = get_actorManager->GetAllHeros();
    if (GetAllHeros == nullptr) return;

    ActorLinker **actorLinkers = (ActorLinker **)GetAllHeros->getItems();

    for (int i = 0; i < GetAllHeros->getSize(); i++) {
        ActorLinker *actorLinker = actorLinkers[(i * 2) + 1];
        if (actorLinker == nullptr) continue;

        if (actorLinker->IsHostPlayer()) {
            rotation = actorLinker->get_rotation();
            EnemyTarget.myPos = actorLinker->get_position();
            EnemyTarget.ConfigID = actorLinker->ObjLinker()->ConfigID();
            EnemyTarget.myObjCamp = actorLinker->get_objCamp();
        }

        if (actorLinker->IsHostCamp() || !actorLinker->get_bVisible() || actorLinker->ValueComponent()->get_actorHp() < 1) continue;

        Vector3 EnemyPos = actorLinker->get_position();
        float Health = actorLinker->ValueComponent()->get_actorHp();
        float MaxHealth = actorLinker->ValueComponent()->get_actorHpTotal();
        int HealthPercent = (int)std::round((float)Health / MaxHealth * 100);

        float Distance = Vector3::Distance(EnemyTarget.myPos, EnemyPos);
        float Direction = SquaredDistance(RotateVectorByQuaternion(rotation), calculateSkillDirection(EnemyTarget.myPos, EnemyPos, actorLinker->isMoving(), actorLinker->get_logicMoveForward()));

        if (Distance < 25.f) {
            if (aimType == 1 && Health < minHealth) {
                Entity = actorLinker;
                minHealth = Health;
            }
        }

        if (Entity != NULL) {
            EnemyTarget.enemyPos = Entity->get_position();
            EnemyTarget.moveForward = Entity->get_logicMoveForward();
            EnemyTarget.isMoving = Entity->isMoving();
        }
    }
    
    return _UpdateLogic(instance, delta);
}

void (*_SendMoveDirection)(void *instance, Vector2 a, Vector2 b);
void SendMoveDirection(void *instance, Vector2 a, Vector2 b) {
    if (isAutoPlayFlorentino) {
        size_t initialObjectCount = gameObject->objects->size();
        for (int i = 0; i < initialObjectCount; i++) {
            ActorLinker *linker = ((ActorLinker*)(*gameObject->objects)[i]->object);
            if (!linker) return _SendMoveDirection(instance, a, b);

            Vector3 linkerPosition = linker->get_position();
            float disToEnemy = Vector3::Distance(EnemyTarget.myPos, EnemyTarget.enemyPos);
            float disToFlower = Vector3::Distance(EnemyTarget.myPos, linker->get_position());

            if (disToEnemy < 7.0f) {
                const float epsilon = 0.1f;
                if (fabs(EnemyTarget.myPos.x - linker->get_position().x) < epsilon &&
                    fabs(EnemyTarget.myPos.z - linker->get_position().z) < epsilon) {
                    return;
                }

                Vector3 direction = linkerPosition - EnemyTarget.myPos;
                Vector2 direction2D = {direction.x, direction.z};

                if (EnemyTarget.myObjCamp == 1) {
                    direction2D.x = direction2D.x;
                    direction2D.y = direction2D.y;
                } else {
                    direction2D.x = -direction2D.x;
                    direction2D.y = -direction2D.y;
                }

                float length = sqrt(direction2D.x * direction2D.x + direction2D.y * direction2D.y);
                if (length != 0) {
                    direction2D.x /= length;
                    direction2D.y /= length;
                }

                float speed = 284.0f;
                Vector2 moveDirection = {direction2D.x * speed, direction2D.y * speed};
                return _SendMoveDirection(instance, a, moveDirection);
            }
        }
    }
    _SendMoveDirection(instance, a, b);
}


void hack_prepare(const char *_game_data_dir) {
    while (!il2cppMap) {
        il2cppMap = Tools::GetBaseAddress(TargetLibName);
        sleep(2);
    }
    
	Il2Cpp::Il2CppAttach();
   
    
    gameObject = new GameObject();
    
    Tools::Hook((void *) (uint64_t)Il2Cpp::Il2CppGetMethodOffset(OBFUSCATE("Project.Plugins_d.dll"), OBFUSCATE("NucleusDrive.Logic"), OBFUSCATE("LVActorLinker") , OBFUSCATE("SetVisible"), 3), (void *) LActorRoot_Visible, (void **) &_LActorRoot_Visible);

    
    
    
    Tools::Hook(
      (void *)(uintptr_t)Il2Cpp::Il2CppGetMethodOffset(
          OBFUSCATE("Project_d.dll"), OBFUSCATE("Assets.Scripts.GameLogic"),
          OBFUSCATE("GameInput"), OBFUSCATE("SendMoveDirection"), 2),
      (void *)SendMoveDirection, (void **)&_SendMoveDirection);
    
    
}
