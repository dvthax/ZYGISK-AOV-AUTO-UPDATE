#ifndef ZYGISK_IMGUI_MODMENU_GAME_H
#define ZYGISK_IMGUI_MODMENU_GAME_H

#include "Includes/obfuscate.h"
// TODO: change this
#define TargetLibName "libil2cpp.so"

const static char* allowed_packages[] = {
    OBFUSCATE("com.ngame.allstar.eu"),    // Máy chủ Châu Âu
    OBFUSCATE("com.ngame.allstar.india"), // Máy chủ Ấn Độ
    OBFUSCATE("com.garena.game.kgtw"),    // Máy chủ Đài Loan
    OBFUSCATE("com.garena.game.kgth"),    // Máy chủ Thái Lan
    OBFUSCATE("com.garena.game.kgvn"),    // Máy chủ Việt Nam
    OBFUSCATE("com.tencent.ngjp"),        // Máy chủ Nhật Bản
    OBFUSCATE("com.garena.game.kgsam"),   // Máy chủ Đông Nam Á (Philippines, Malaysia, Singapore)
    OBFUSCATE("com.tencent.ngame.chty")   // Máy chủ thử nghiệm (Trung Quốc)
};

#endif //ZYGISK_IMGUI_MODMENU_GAME_H
