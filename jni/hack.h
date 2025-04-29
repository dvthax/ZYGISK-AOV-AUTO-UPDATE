#ifndef ZYGISK_IMGUI_MODMENU_HACK_H
#define ZYGISK_IMGUI_MODMENU_HACK_H

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <dlfcn.h>
#include <string>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <cmath>
#include "Includes/obfuscate.h"
uintptr_t il2cppMap;
#include "game.h"
#include "Tools.h"
#include "xdl.h"
#include "Unity/Unity.h"
#include "Unity/Vector3.hpp"
#include "Unity/VInt3.hpp"
#include "Il2CppSDK/Call.h"
#include "GameObject/GameObject.h"

GameObject *gameObject;


#define OBFUSCATE_METHOD(image, namespaze, clazz, name, args) \
Il2Cpp::Il2CppGetMethodOffset(OBFUSCATE(image), OBFUSCATE(namespaze), OBFUSCATE(clazz), OBFUSCATE(name), args)

#define OBFUSCATE_FIELD(image, namespaze, clazz, name)                 \
  Il2Cpp::Il2CppGetFieldOffset(OBFUSCATE(image), OBFUSCATE(namespaze), \
                               OBFUSCATE(clazz), OBFUSCATE(name))


class Camera {
    public:
        static Camera *get_main() {
        Camera *(*get_main_) () = (Camera *(*)())OBFUSCATE_METHOD("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "get_main", 0);
        return get_main_();
    }
    
    Vector3 WorldToScreenPoint(Vector3 position) {
        Vector3 (*WorldToScreenPoint_)(Camera *camera, Vector3 position) = (Vector3 (*)(Camera *, Vector3))OBFUSCATE_METHOD("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "WorldToScreenPoint", 1);
        return WorldToScreenPoint_(this, position);
    }
};

class ValueLinkerComponent {
    public:
        int get_actorHp() {
            int (*get_actorHp_)(ValueLinkerComponent * objLinkerWrapper) = (int (*)(ValueLinkerComponent *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ValueLinkerComponent", "get_actorHp", 0);
            return get_actorHp_(this);
        }

        int get_actorHpTotal() {
            int (*get_actorHpTotal_)(ValueLinkerComponent * objLinkerWrapper) =
                (int (*)(ValueLinkerComponent *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ValueLinkerComponent", "get_actorHpTotal", 0);
            return get_actorHpTotal_(this);
        }
};



class CActorInfo {
    public:
        string *ActorName() {
            return *(string **)((uintptr_t)this + 0xC);
        }

        int hudHeight() {
            return *(int *)((uintptr_t)this + 0x70); 
        }
};


class ActorConfig{
    public:
    
    int ConfigID() {
        return *(int *) ((uintptr_t) this + 0x10); //public Int32 ConfigID; // 0x10
    }
};


class ActorLinker {
    public:
        ValueLinkerComponent *ValueComponent() {
    return *(ValueLinkerComponent *
                 *)((uintptr_t)this +
                    OBFUSCATE_FIELD(
                        "Project_d.dll", "Kyrios.Actor", "ActorLinker",
                        "ValueComponent"));  // public ValueLinkerComponent
                                             // ValueComponent; // 0x18
  }

  ActorConfig *ObjLinker() {
    return *(ActorConfig *
                 *)((uintptr_t)this +
                    OBFUSCATE_FIELD(
                        "Project_d.dll", "Kyrios.Actor", "ActorLinker",
                        "ObjLinker"));  // public ActorConfig ObjLinker; // 0x9C
  }
        Vector3 get_position() {
            Vector3 (*get_position_)(ActorLinker * linker) = (Vector3(*)(ActorLinker *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorLinker", "get_position", 0);
            return get_position_(this);
        }
        Quaternion get_rotation() {
            Quaternion (*get_rotation_)(ActorLinker *linker) = (Quaternion (*)(ActorLinker *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorLinker", "get_rotation", 0);
            return get_rotation_(this);
        }
        bool IsHostCamp() {
            bool (*IsHostCamp_)(ActorLinker *linker) = (bool (*)(ActorLinker *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorLinker", "IsHostCamp", 0);
            return IsHostCamp_(this);
        }
        
        bool IsHostPlayer() {
            bool (*IsHostPlayer_)(ActorLinker *linker) = (bool (*)(ActorLinker *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorLinker", "IsHostPlayer", 0);
            return IsHostPlayer_(this);
        }
        bool isMoving() {
    return *(bool *)((uintptr_t)this +
                     OBFUSCATE_FIELD(
                         "Project_d.dll", "Kyrios.Actor", "ActorLinker",
                         "isMoving"));  //  public bool isMoving; // 0x2F2
  }

        Vector3 get_logicMoveForward() {
            Vector3 (*get_logicMoveForward_)(ActorLinker *linker) = (Vector3 (*)(ActorLinker *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorLinker", "get_logicMoveForward", 0);
            return get_logicMoveForward_(this);
        }
        bool get_bVisible() {
            bool (*get_bVisible_)(ActorLinker *linker) = (bool (*)(ActorLinker *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorLinker", "get_bVisible", 0);
            return get_bVisible_(this);
        }
        
        int get_playerId() {
            int (*get_playerId_)(ActorLinker *linker) = (int (*)(ActorLinker *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorLinker", "get_playerId", 0);
            return get_playerId_(this);
        }
        
        int get_ObjID() {
            int (*get_ObjID_)(ActorLinker *linker) = (int (*)(ActorLinker *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorLinker", "get_ObjID", 0);
            return get_ObjID_(this);
        }
        
        int get_objType() {
            int (*get_objType_)(ActorLinker *linker) = (int (*)(ActorLinker *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorLinker", "get_objType", 0);
            return get_objType_(this);
        }
        
        
        int get_objCamp() {
    static const auto _ =
        reinterpret_cast<int(__fastcall *)(ActorLinker *)>(OBFUSCATE_METHOD(
            "Project_d.dll", "Kyrios.Actor", "ActorLinker", "get_objCamp", 0));
    return _ ? _(this) : 0;
  }
        
            
};

class ActorManager {
    public:
    
    List<ActorLinker *> *GetAllHeros() {
        List<ActorLinker *> *(*_GetAllHeros)(ActorManager *actorManager) = (List<ActorLinker *> *(*)(ActorManager *))OBFUSCATE_METHOD("Project_d.dll", "Kyrios.Actor", "ActorManager", "GetAllHeros", 0);
        return _GetAllHeros(this);
    }
};

class KyriosFramework {
    public:
    
    static ActorManager *get_actorManager() {
        auto get_actorManager_ = (ActorManager *(*)())OBFUSCATE_METHOD("Project_d.dll", "Kyrios", "KyriosFramework", "get_actorManager", 0);
        return get_actorManager_();
    }
};

class PlayerMovement {
public:
    static Vector3 get_velocity(PlayerMovement* instance) {
        if (instance == nullptr) return Vector3::zero();

        VInt3 vint3_velocity = ((VInt3(*)(PlayerMovement*))OBFUSCATE_METHOD("Project.Plugins_d.dll", "NucleusDrive.Logic", "PlayerMovement", "get_velocity", 0))(instance);
        return Vector3(vint3_velocity.X / 1000.0f, vint3_velocity.Y / 1000.0f, vint3_velocity.Z / 1000.0f); // Sử dụng X, Y, Z
    }

    static Vector3 VInt3ToVector3(VInt3 vint3) {
        return Vector3(vint3.X / 1000.0f, vint3.Y / 1000.0f, vint3.Z / 1000.0f); // Sử dụng X, Y, Z
    }
};

class LActorRoot {
 public:
  // ... (các khai báo khác)

  
  int GiveMyEnemyCamp() {
    int (*_GiveMyEnemyCamp)(LActorRoot *actor) =
        (int (*)(LActorRoot *))OBFUSCATE_METHOD(
            "Project.Plugins_d.dll", "NucleusDrive.Logic", "LActorRoot",
            "GiveMyEnemyCamp", 0);

    return _GiveMyEnemyCamp(this);
  }

  VInt3 get_location() {
    VInt3 (*_get_location)(LActorRoot *instance) =
        (VInt3(*)(LActorRoot *))OBFUSCATE_METHOD(
            "Project.Plugins_d.dll", "NucleusDrive.Logic", "LActorRoot",
            "get_location", 0);
    return _get_location(this);
  }

  VInt3 get_forward() {
    VInt3 (*_get_forward)(LActorRoot *instance) =
        (VInt3(*)(LActorRoot *))OBFUSCATE_METHOD(
            "Project.Plugins_d.dll", "NucleusDrive.Logic", "LActorRoot",
            "get_forward", 0);
    return _get_forward(this);
  }
};



class SkillSlot {
 public:
  int nSkill() {
    int slot = *(int *)((uintptr_t)this +
                        Il2Cpp::Il2CppGetFieldOffset("Project_d.dll",
                                                     "Assets.Scripts.GameLogic",
                                                     "SkillSlot", "SlotType"));
    return slot;
  }

  bool get_IsCDReady() {
    bool (*get_IsCDReady_)(SkillSlot *instance) =
        (bool (*)(SkillSlot *))OBFUSCATE_METHOD(
            "Project_d.dll", "Assets.Scripts.GameLogic", "SkillSlot",
            "get_IsCDReady", 0);
    return get_IsCDReady_(this);
  }

  void RequestUseSkill() {
    void (*RequestUseSkill_)(SkillSlot *instance) =
        (void (*)(SkillSlot *))OBFUSCATE_METHOD(
            "Project_d.dll", "Assets.Scripts.GameLogic", "SkillSlot",
            "RequestUseSkill", 0);
    return RequestUseSkill_(this);
  }

  void ReadyUseSkill(bool bForceSkillUseInDefaultPosition) {
    void (*ReadyUseSkill_)(SkillSlot *instance,
                           bool bForceSkillUseInDefaultPosition) =
        (void (*)(SkillSlot *, bool))OBFUSCATE_METHOD(
            "Project_d.dll", "Assets.Scripts.GameLogic", "SkillSlot",
            "ReadyUseSkill", 1);
    return ReadyUseSkill_(this, bForceSkillUseInDefaultPosition);
  }
};

struct SkillInfo {
  SkillSlot *skill0, *skill1, *skill2, *skill3, *skill4, *skill5, *skill6,
      *skill7, *skill8, *skill9, *skill10;

  void setInstance(SkillSlot *instance) {
    if (!instance) return;
    int slot = instance->nSkill();
    switch (slot) {
      case 0:
        skill0 = instance;
        break;
      case 1:
        skill1 = instance;
        break;
      case 2:
        skill2 = instance;
        break;
      case 3:
        skill3 = instance;
        break;
      case 4:
        skill4 = instance;
        break;
      case 5:
        skill5 = instance;
        break;
      case 6:
        skill6 = instance;
        break;
      case 7:
        skill7 = instance;
        break;
      case 8:
        skill8 = instance;
        break;
      case 9:
        skill9 = instance;
        break;
      case 10:
        skill10 = instance;
        break;
    }
  }
  
  
  SkillSlot * getInstance(int slot)
  {
      SkillSlot *skillSlot;
      switch (slot) {
      case 0:
        skillSlot = skill0;
        break;
      case 1:
        skillSlot = skill1;
        break;
      case 2:
        skillSlot = skill2;
        break;
      case 3:
        skillSlot = skill3;
        break;
      case 4:
        skillSlot = skill4;
        break;
      case 5:
        skillSlot = skill5;
        break;
      case 6:
        skillSlot = skill6;
        break;
      case 7:
        skillSlot = skill7;
        break;
      case 8:
        skillSlot = skill8;
        break;
      case 9:
        skillSlot = skill9;
        break;
      case 10:
        skillSlot = skill10;
        break;
    }
    
    
    return skillSlot;
    
  }
} skillIn4{};


void hack_prepare(const char *game_data_dir);

#endif //ZYGISK_IMGUI_MODMENU_HACK_H
