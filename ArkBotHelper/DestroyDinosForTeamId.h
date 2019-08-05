#pragma once
#include "ArkBotHelper.h"

std::string DestroyDinosForTeamIdInternal(FString* cmd)
{
	TArray<FString> Parsed;
	cmd->ParseIntoArray(Parsed, L" ", true);

	if (Parsed.IsValidIndex(1))
	{
		int teamId;

		try
		{
			teamId = std::stoi(*Parsed[1]);
		}
		catch (const std::exception&)
		{
			return {};
		}

		if (teamId < 10000) return {};

		UWorld* world = ArkApi::GetApiUtils().GetWorld();
		if (!world) return {};

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(world, APrimalDinoCharacter::GetPrivateStaticClass(), &FoundActors);

		int num = 0;
		for (const auto& actor : FoundActors)
		{
			APrimalDinoCharacter* dino = static_cast<APrimalDinoCharacter*>(actor);

			int dinoTeam = dino->TargetingTeamField();
			if (dinoTeam == teamId)
			{
				dino->Suicide();
				num++;
			}
		}
		std::string response = fmt::format("Destroyed {} dios belonging to team {}", num, teamId);

		return response;
	}

	return {};
}
