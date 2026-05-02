#pragma once

inline TAutoConsoleVariable<float> CVarProjectileDrawDebug{TEXT("rogue.projectile.DebugDraw"), 0.f, 
	TEXT("Draw projectile traces. (0=off. >0 is draw duration"), ECVF_Cheat};


inline TAutoConsoleVariable<bool> CVarMinionRangedDrawDebug{TEXT("rogue.ai.minionranged.DebugDraw"), true,
	TEXT("Draw MinionRanged related shapes. (0=off, 1=on)"), ECVF_Cheat};
