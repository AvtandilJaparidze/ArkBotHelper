#pragma once
#include "ArkBotHelper.h"

std::string DestroyAllStructuresForTeamIdInternal(FString* cmd)
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

		UGameplayStatics::GetAllActorsOfClass(world, APrimalStructure::GetPrivateStaticClass(), &FoundActors);

		//todo: maybe destroy rafts aswell?
		int num = 0;
		for (const auto& actor : FoundActors)
		{
			APrimalStructure* structure = static_cast<APrimalStructure*>(actor);

			int structureTeam = structure->TargetingTeamField();
			if (structureTeam == teamId)
			{
				APrimalStructureItemContainer* StructInv = static_cast<APrimalStructureItemContainer*>(structure);
				//UPrimalInventoryComponent* inventory = StructInv->MyInventoryComponentField();
				if (StructInv) StructInv->bDropInventoryOnDestruction() = false;
				
				structure->Suicide();
				num++;
			}
		}
		std::string response = fmt::format("Destroyed {} structures belonging to team {}", num, teamId);

		return response;
	}

	return {};
}
