#include "ArkBotHelper.h"
#include "DestroyDinosForTeamId.h"
#include "DestroyStructuresForTeamId.h"
#include "DestroyStructuresForTeamIdAtPos.h"
//#include "DoRespec.h"
//#include "DoRespecDino.h"
//#include "DroppedEggs.h"
//#include "FeedDinosForTeamId.h"

#pragma comment(lib, "ArkApi.lib")

/*void DoRespecRconCommand(RCONClientConnection* rconClientConnection, RCONPacket* rconPacket, UWorld* uWorld)
{
	FString msg = rconPacket->Body;

	auto result = DoRespecInternal(&msg);
	if (result.length() == 0) return;

	FString reply(result.c_str());
	reply.AppendChar(L'\n');
	rconClientConnection->SendMessageW(rconPacket->Id, 0, &reply);
}

void DoRespecDinoRconCommand(RCONClientConnection* rconClientConnection, RCONPacket* rconPacket, UWorld* uWorld)
{
	FString msg = rconPacket->Body;

	auto result = DoRespecDinoInternal(&msg, nullptr);
	if (result.length() == 0) return;

	FString reply(result.c_str());
	reply.AppendChar(L'\n');
	rconClientConnection->SendMessageW(rconPacket->Id, 0, &reply);
}*/

void DestroyAllStructuresForTeamIdRconCommand(RCONClientConnection* rconClientConnection, RCONPacket* rconPacket, UWorld* uWorld)
{
	FString msg = rconPacket->Body;

	auto result = DestroyAllStructuresForTeamIdInternal(&msg);
	if (result.length() == 0) return;

	FString reply(result.c_str());
	reply.AppendChar(L'\n');
	rconClientConnection->SendMessageW(rconPacket->Id, 0, &reply);
}

void DestroyStructuresForTeamIdAtPositionRconCommand(RCONClientConnection* rconClientConnection, RCONPacket* rconPacket, UWorld* uWorld)
{
	FString msg = rconPacket->Body;

	auto result = DestroyStructuresForTeamIdAtPositionInternal(&msg);
	if (result.length() == 0) return;

	FString reply(result.c_str());
	reply.AppendChar(L'\n');
	rconClientConnection->SendMessageW(rconPacket->Id, 0, &reply);
}

void DestroyDinosForTeamIdRconCommand(RCONClientConnection* rconClientConnection, RCONPacket* rconPacket, UWorld* uWorld)
{
	FString msg = rconPacket->Body;

	auto result = DestroyDinosForTeamIdInternal(&msg);
	if (result.length() == 0) return;

	FString reply(result.c_str());
	reply.AppendChar(L'\n');
	rconClientConnection->SendMessageW(rconPacket->Id, 0, &reply);
}

/*void DroppedEggsRconCommand(RCONClientConnection* rconClientConnection, RCONPacket* rconPacket, UWorld* uWorld)
{
	FString msg = rconPacket->Body;

	auto result = DroppedEggsInternal(&msg);
	if (result.length() == 0) return;

	FString reply(result.c_str());
	reply.AppendChar(L'\n');
	rconClientConnection->SendMessageW(rconPacket->Id, 0, &reply);
}

void FeedDinosForTeamIdRconCommand(RCONClientConnection* rconClientConnection, RCONPacket* rconPacket, UWorld* uWorld)
{
	FString msg = rconPacket->Body;

	auto result = FeedDinosForTeamIdInternal(&msg);
	if (result.length() == 0) return;

	FString reply(result.c_str());
	reply.AppendChar(L'\n');
	rconClientConnection->SendMessageW(rconPacket->Id, 0, &reply);
}*/

void Load()
{
	Log::Get().Init("ArkBotHelper");
	try
	{
		auto& commands = ArkApi::GetCommands();
			//commands.AddRconCommand("DoRespec", &DoRespecRconCommand);
			//commands.AddRconCommand("DoRespecDino", &DoRespecDinoRconCommand);
			commands.AddRconCommand("DestroyAllStructuresForTeamId", &DestroyAllStructuresForTeamIdRconCommand);
			commands.AddRconCommand("DestroyStructuresForTeamIdAtPosition", &DestroyStructuresForTeamIdAtPositionRconCommand);
			commands.AddRconCommand("DestroyDinosForTeamId", &DestroyDinosForTeamIdRconCommand);
			//commands.AddRconCommand("DroppedEggs", &DroppedEggsRconCommand);
			//commands.AddRconCommand("FeedDinosForTeamId", &FeedDinosForTeamIdRconCommand);
	}
	catch (const std::exception& error)
	{
		Log::GetLog()->error(error.what());
		throw;
	}

}

void Unload()
{
	auto& commands = ArkApi::GetCommands();
	//commands.RemoveRconCommand("DoRespec");
	//commands.RemoveRconCommand("DoRespecDino");
	commands.RemoveRconCommand("DestroyAllStructuresForTeamId");
	commands.RemoveRconCommand("DestroyStructuresForTeamIdAtPosition");
	commands.RemoveRconCommand("DestroyDinosForTeamId");
	//commands.RemoveRconCommand("DroppedEggs");
	//commands.RemoveRconCommand("FeedDinosForTeamId");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Load();
		break;
	case DLL_PROCESS_DETACH:
		Unload();
		break;
	}
	return TRUE;
}