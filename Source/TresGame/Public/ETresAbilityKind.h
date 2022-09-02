#pragma once
#include "CoreMinimal.h"
#include "ETresAbilityKind.generated.h"

UENUM(BlueprintType)
enum class ETresAbilityKind : uint8 {
    NONE,
    AIR_RECOVERY,
    BLOW_COUNTER,
    REFLECT_GUARD,
    GUARD_COUNTER,
    REVENGEIMPACT,
    REVENGEDIVE,
    REVENGE_EX,
    RISKDODGE,
    RD_COUNTER,
    SLASH_UPPER,
    AIR_ROLL_BEAT,
    AIR_DOWN,
    TRIPPLE_SLASH,
    CHARGE_THRUST,
    MAGICFLUSH,
    HIGHJUMP,
    DOUBLEFLIGHT,
    SUPERJUMP,
    SUPERSLIDE,
    GLIDE,
    LIBRA,
    DODGE,
    AIRSLIDE,
    AIRDODGE,
    MP_SAFETY,
    EXPZERO,
    FRIEND_AID,
    COMBO_PLUS,
    AIRCOMBO_PLUS,
    COMBO_MASTER,
    COMBO_UP,
    AIRCOMBO_UP,
    FIRE_UP,
    BLIZZARD_UP,
    THUNDER_UP,
    WATER_UP,
    AERO_UP,
    WIZZARD_STAR,
    LUCK_UP,
    ITEM_UP,
    PRIZE_DRAW,
    FOCUS_BOOST,
    LEAF_VEIL,
    LAST_LEAVE,
    COMBO_LEAVE,
    FOCUS_ASPIR,
    ATTRACTION_TIME,
    LINK_BOOST,
    FORM_TIME,
    DEFENDER,
    CRITICAL_HALF,
    DAMAGE_ASPIR,
    MP_HASTE,
    MP_HASTERA,
    MP_HASTEGA,
    MAGIC_COMBO_SAVE,
    MAGIC_COMBO_UP,
    WALK_REGENE,
    WALK_HEALING,
    MAGIC_DRAW,
    MASTER_DRAW,
    ATTRACTION_UP,
    BURN_GUARD,
    CLOUD_GUARD,
    SNEEZE_GUARD,
    FREEZE_GUARD,
    DISCHARGE_GUARD,
    STUN_GUARD,
    COUNTER_UP,
    AUTO_FINISH,
    FORM_UP,
    MAGIC_TIME,
    AUTO_LOCK_MAGIC,
    GUARD_REGENE,
    MP_SAVE,
    MP_LEAVE,
    FULLMP_BURST,
    HARVEST,
    HP_CONVERTER,
    MP_CONVERTER,
    MUNNY_CONVERTER,
    ENDLESS_MAGIC,
    FP_CONVERTER,
    FIRE_ASPIR,
    BLIZZARD_ASPIR,
    THUNDER_ASPIR,
    WATER_ASPIR,
    AERO_ASPIR,
    DARK_ASPIR,
    BEST_COMBI,
    SONIC_SLASH,
    SONIC_DOWN,
    TURN_CUTTER,
    SUMMERSALT,
    POLE_SPIN,
    POLE_SWING,
    WALL_KICK,
    BATTLE_GRAPHER,
    CHARISMA_CHEF,
    JOIN_FORCE,
    HEARTLESS_BUSTER,
    NOBODY_BUSTER,
    POWER_CURE,
    CRITICAL_COUNTER,
    CRITICAL_CHARGE,
    CRITICAL_CONVERTER,
    QUICK_SHAFT,
    FLASH_STEP,
    RADIAL_CUT,
    FINAL_HEAVEN,
    AERIAL_SWEEP,
    AERIAL_DIVE,
    LUNCH_TIME = 0xAA,
    POWER_LUNCH,
    OVER_TIME,
    BEST_CONDITION,
    EXP_BARGAIN,
    PRIZE_FEEVER,
    MILLIONAIRE,
    CURAGAN,
    CHARGE_BERSERK,
    OVERCOME,
    GRAND_MAGIC,
    FIRAGAN,
    BLIZZAGAN,
    THUNDAGAN,
    WATAGAN,
    AEROGAN,
    MAGIC_ROULETTE,
    UNISON_FIRE = 0xBE,
    UNISON_BLIZZARD,
    UNISON_THUNDER,
    FUSION_SPIN,
    FUSION_ROCKET,
    HYPER_HEALING,
    COMBI_UP,
    COMBI_TIME,
    SHARE_PRIZE,
    MICKEY_CURE,
    MICKEY_HOLY,
    DONALD_FIRE,
    DONALD_BLIZZARD,
    DONALD_THUNDER,
    DONALD_AERO,
    DONALD_CURE,
    GOOFY_TORNADE,
    GOOFY_TURBO,
    GOOFY_FLIP,
    HERCULES_ROCKTHROW,
    HERCULES_ENERGYBURST,
    WOODY_SHOULDERTACKLE,
    WOODY_ROPEATTACK,
    BUZZ_BEAM,
    BUZZ_DOUBLELARIAT,
    RAPUNZEL_HAIRSWING,
    RAPUNZEL_HAIRROTATION,
    FLYNN_THROWFRYINGPAN,
    FLYNN_BARRELBASH,
    SULLEY_ROAR,
    SULLEY_SHOULDERTACKLE,
    MIKE_MIKEAPPEAL,
    MIKE_SUPPORT,
    SPARROW_BONECRASH,
    SPARROW_TWISTROLLING,
    MARSHMALLOW_JUMPSTRIKE,
    MARSHMALLOW_COLDBREATH,
    BAYMAX_ROCKETPUNCH,
    BAYMAX_CURESPRAY,
    RIKU_DARKFIRE,
    RIKU_SHADOWBREAKER,
    VENTUS_WINDRAID,
    AQUA_BLIZZAGA,
    AQUA_THUNDAGA,
    AQUA_CURAGA,
    ROXAS_CROSSSHOT,
    ROXAS_CROSSBRADE,
    XION_CURAGA,
    XION_LASERRAIN,
    __LEA_FIRAGARAID,
    LEA_FIRAGASLICER,
    KAIRI_CURE,
    SORA_FIRAGA,
    SORA_CURAGA,
    TRES_ABI_KIND_MAX UMETA(Hidden),
};
