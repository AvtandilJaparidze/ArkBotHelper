#pragma once
#include "ArkBotHelper.h"

std::string DestroyStructuresForTeamIdAtPositionInternal(FString* cmd)
{
	TArray<FString> Parsed;
	cmd->ParseIntoArray(Parsed, L" ", true);

	if (Parsed.IsValidIndex(5))
	{
		int teamId;
		float x;
		float y;
		//float z;
		float radius;
		bool rafts;

		try
		{
			teamId = std::stoi(*Parsed[1]);
			x = std::stof(*Parsed[2]);
			y = std::stof(*Parsed[3]);
			radius = std::stof(*Parsed[4]);
			rafts = (bool)std::stoi(*Parsed[5]);
			//z = std::stof(*Parsed[4]);
		}
		catch (const std::exception&)
		{
			return {};
		}

		if (teamId < 10000) return {};
		if (radius <= 0) return {};

		UWorld* world = ArkApi::GetApiUtils().GetWorld();
		if (!world) return {};

		int num = 0;
		FVector pos;

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(world, APrimalStructure::GetPrivateStaticClass(), &FoundActors);

		for (const auto& actor : FoundActors)
		{
			APrimalStructure* structure = static_cast<APrimalStructure*>(actor);

			int structureTeam = structure->TargetingTeamField();
			structure->RootComponentField()->GetCustomLocation(&pos);
			//if (structureTeam == teamId && ArkLibrary::IsPointInsideSphere(pos, x, y, z, radius))
			if (structureTeam == teamId && IsPointInside2dCircle(pos, x, y, radius))
			{
				APrimalStructureItemContainer* StructInv = static_cast<APrimalStructureItemContainer*>(structure);
				//UPrimalInventoryComponent* inventory = StructInv->MyInventoryComponentField();
				if (StructInv) StructInv->bDropInventoryOnDestruction() = false;
				
				structure->Suicide();
				num++;
			}
		}

		if (rafts) {
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(world, APrimalDinoCharacter::GetPrivateStaticClass(), &FoundActors);

			for (const auto& actor : FoundActors)
			{
				APrimalDinoCharacter* dino = static_cast<APrimalDinoCharacter*>(actor);

				int dinoTeam = dino->TargetingTeamField();

				dino->RootComponentField()->GetCustomLocation(&pos);
				//if (structureTeam == teamId && ArkLibrary::IsPointInsideSphere(pos, x, y, z, radius))
				if (dinoTeam == teamId && IsPointInside2dCircle(pos, x, y, radius))
				{
					FString className;
					FName bp = actor->NameField();
					bp.ToString(&className);

					if (className.Contains("Raft_BP_C") || className.Contains("MotorRaft_BP_C")) {
						dino->Destroy(false, true);
						num++;
					}

				}
			}
		}

		//ss << "Destroyed " << num << " structures belonging to team " << teamId << " at position (x: " << x << ", y: " << y << ", z: " << z << ", r: " << radius << ")";
		std::string response = fmt::format("Destroyed {} structures belonging to team {} at position (x={}, y={}, r={}, rafts={})", num, teamId, x, y, radius, rafts);

		return response;
	}

	return {};
}