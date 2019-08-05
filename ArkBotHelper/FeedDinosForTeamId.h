#pragma once
#include "ArkBotHelper.h"

std::string FeedDinosForTeamIdInternal(FString* cmd)
{
	TArray<FString> Parsed;
	cmd->ParseIntoArray(Parsed, L" ", true);

	if (Parsed.IsValidIndex(1))
	{
		__int64 teamId;

		try
		{
			teamId = std::stoull(*Parsed[1]);
		}
		catch (const std::exception&)
		{
			return {};
		}

		if (teamId < 50000) return {};

		UWorld* world = ArkApi::GetApiUtils().GetWorld();
		if (!world) return {};

		TArray<AActor*>* FoundActors = new TArray<AActor*>();
		UGameplayStatics::GetAllActorsOfClass(world, APrimalDinoCharacter::GetPrivateStaticClass(), FoundActors);

		int num = 0;
		for (uint32_t i = 0; i < FoundActors->Num(); i++)
		{
			AActor* actor = (*FoundActors)[i];

			APrimalDinoCharacter* dino = static_cast<APrimalDinoCharacter*>(actor);

			int dinoTeam = dino->TargetingTeamField();
			if (dinoTeam == teamId)
			{
				FString* className = new FString();
				FName bp = actor->NameField();
				bp.ToString(className);
				std::string classNameStr = className->ToString();

				if (classNameStr.compare("Raft_BP_C") != 0 && classNameStr.compare("MotorRaft_BP_C") != 0)
				{
					UPrimalCharacterStatusComponent* status = dino->MyCharacterStatusComponentField();
					if (status)
					{
						// 0: health
						// 1: stamina
						// 2: torpor
						// 3: oxygen
						// 4: food
						// 5: water
						// 6: temperature
						// 7: weight
						// 8: melee damage
						// 9: movement speed
						// 10: fortitude
						// 11: crafting speed
						float* maxStatsValues = status->MaxStatusValuesField()();
						float* currentStatValues = status->CurrentStatusValuesField()();
						currentStatValues[4] = maxStatsValues[4];

						num++;
					}
				}

				delete className;
			}
		}
		std::string response = fmt::format("Fed {} dinos belonging to team {}", num, teamId);

		delete FoundActors;
		return response;
	}

	return {};
}

