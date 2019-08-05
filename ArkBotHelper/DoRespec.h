#pragma once
#include "ArkBotHelper.h"

std::wstring DoRespecInternal(FString* cmd)
{
	TArray<FString> Parsed;
	cmd->ParseIntoArray(Parsed, L" ", true);

	if (Parsed.IsValidIndex(1))
	{
		uint64 steamId;

		try
		{
			steamId = std::stoull(*Parsed[1]);
		}
		catch (const std::exception&)
		{
			return {};
		}

		auto aShooterPC = ArkApi::GetApiUtils().FindPlayerFromSteamId(steamId);
		if (aShooterPC)
		{
			auto stateField = aShooterPC->GetPlayerCharacter()->PlayerStateField();
			auto playerState = static_cast<AShooterPlayerState*>(stateField);
			if (playerState)
			{
				//todo: this works - but how does it compare to the way the game does it?
				playerState->DoRespec(nullptr, nullptr, false);

				return L"Successfully triggered player respec";
			}
		}
	}

	return {};
}