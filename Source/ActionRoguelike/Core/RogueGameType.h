#pragma once

namespace RogueCollision
{
	namespace Trace
	{
		constexpr ECollisionChannel Interaction = ECC_GameTraceChannel1;
	}

	namespace Profile
	{
		inline const FName Projectile = FName(TEXT("Projectile"));
		inline const FName OverlapAll = FName(TEXT("OverlapAll"));
	}
}
