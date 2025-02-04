#include "stdafx.h"
#include "Emu/System.h"
#include "np_structs_extra.h"

LOG_CHANNEL(sceNp);
LOG_CHANNEL(sceNp2);

// Helper functions for printing

namespace extra_nps
{
	void print_userinfo2(const SceNpUserInfo2* user)
	{
		sceNp2.warning("SceNpUserInfo2:");
		sceNp2.warning("npid: %s", static_cast<const char*>(user->npId.handle.data));
		sceNp2.warning("onlineName: *0x%x(%s)", user->onlineName, user->onlineName ? static_cast<const char*>(user->onlineName->data) : "");
		sceNp2.warning("avatarUrl: *0x%x(%s)", user->avatarUrl, user->avatarUrl ? static_cast<const char*>(user->avatarUrl->data) : "");
	}

	void print_sigoptparam(const SceNpMatching2SignalingOptParam* opt)
	{
		sceNp2.warning("SceNpMatching2SignalingOptParam:");
		sceNp2.warning("type: %d", opt->type);
		sceNp2.warning("flag: %d", opt->flag);
		sceNp2.warning("hubMemberId: %d", opt->hubMemberId);
	}

	void print_bin_attr(const SceNpMatching2BinAttr* bin)
	{
		const auto ptr = +bin->ptr;
		const u32 size = bin->size;

		sceNp2.warning("Id: %d, Size: %d, ptr: 0x%x", bin->id, size, ptr);

		if (ptr && size)
		{
			sceNp2.warning("Data: %s", std::basic_string_view<u8>{ptr.get_ptr(), size});
		}
	}

	void print_bin_attr_internal(const SceNpMatching2RoomBinAttrInternal* bin)
	{
		sceNp2.warning("updateDate: %llu updateMemberId: %d", bin->updateDate.tick, bin->updateMemberId);
		print_bin_attr(&bin->data);
	}

	void print_member_bin_attr_internal(const SceNpMatching2RoomMemberBinAttrInternal* bin)
	{
		sceNp2.warning("updateDate: %llu", bin->updateDate.tick);
		print_bin_attr(&bin->data);
	}

	void print_presence_data(const SceNpMatching2PresenceOptionData* opt)
	{
		sceNp2.warning("Data: %s", std::basic_string_view<u8>{std::data(opt->data), std::size(opt->data)});
	}

	void print_range(const SceNpMatching2Range* range)
	{
		sceNp2.warning("startIndex: %d", range->startIndex);
		sceNp2.warning("total: %d", range->total);
		sceNp2.warning("size: %d", range->size);
	}

	void print_range_filter(const SceNpMatching2RangeFilter* filt)
	{
		sceNp2.warning("startIndex: %d", filt->startIndex);
		sceNp2.warning("max: %d", filt->max);
	}

	void print_createjoinroom(const SceNpMatching2CreateJoinRoomRequest* req)
	{
		sceNp2.warning("SceNpMatching2CreateJoinRoomRequest:");
		sceNp2.warning("worldId: %d", req->worldId);
		sceNp2.warning("lobbyId: %d", req->lobbyId);
		sceNp2.warning("maxSlot: %d", req->maxSlot);
		sceNp2.warning("flagAttr: 0x%x", req->flagAttr);
		sceNp2.warning("roomBinAttrInternal: *0x%x", req->roomBinAttrInternal);
		sceNp2.warning("roomBinAttrInternalNum: %d", req->roomBinAttrInternalNum);

		for (u32 i = 0; i < req->roomBinAttrInternalNum; i++)
			print_bin_attr(&req->roomBinAttrInternal[i]);

		sceNp2.warning("roomSearchableIntAttrExternal: *0x%x", req->roomSearchableIntAttrExternal);
		sceNp2.warning("roomSearchableIntAttrExternalNum: %d", req->roomSearchableIntAttrExternalNum);
		sceNp2.warning("roomSearchableBinAttrExternal: *0x%x", req->roomSearchableBinAttrExternal);
		sceNp2.warning("roomSearchableBinAttrExternalNum: %d", req->roomSearchableBinAttrExternalNum);
		sceNp2.warning("roomBinAttrExternal: *0x%x", req->roomBinAttrExternal);
		sceNp2.warning("roomBinAttrExternalNum: %d", req->roomBinAttrExternalNum);
		sceNp2.warning("roomPassword: *0x%x", req->roomPassword);
		sceNp2.warning("groupConfig: *0x%x", req->groupConfig);
		sceNp2.warning("groupConfigNum: %d", req->groupConfigNum);
		sceNp2.warning("passwordSlotMask: *0x%x", req->passwordSlotMask);
		sceNp2.warning("allowedUser: *0x%x", req->allowedUser);
		sceNp2.warning("allowedUserNum: %d", req->allowedUserNum);
		sceNp2.warning("blockedUser: *0x%x", req->blockedUser);
		sceNp2.warning("blockedUserNum: %d", req->blockedUserNum);
		sceNp2.warning("joinRoomGroupLabel: *0x%x", req->joinRoomGroupLabel);
		sceNp2.warning("roomMemberBinAttrInternal: *0x%x", req->roomMemberBinAttrInternal);
		sceNp2.warning("roomMemberBinAttrInternalNum: %d", req->roomMemberBinAttrInternalNum);

		for (u32 i = 0; i < req->roomMemberBinAttrInternalNum; i++)
			print_bin_attr(&req->roomMemberBinAttrInternal[i]);

		sceNp2.warning("teamId: %d", req->teamId);
		sceNp2.warning("sigOptParam: *0x%x", req->sigOptParam);

		if (req->sigOptParam)
			print_sigoptparam(req->sigOptParam.get_ptr());

		for (u32 i = 0; i < req->roomSearchableIntAttrExternalNum; i++)
		{
			sceNp2.warning("roomSearchableIntAttrExternal(%d) = %d", req->roomSearchableIntAttrExternal[i].id, req->roomSearchableIntAttrExternal[i].num);
		}
	}

	void print_joinroom(const SceNpMatching2JoinRoomRequest* req)
	{
		sceNp2.warning("SceNpMatching2JoinRoomRequest:");
		sceNp2.warning("roomId: %d", req->roomId);
		sceNp2.warning("roomPassword: *0x%x", req->roomPassword);
		sceNp2.warning("joinRoomGroupLabel: *0x%x", req->joinRoomGroupLabel);
		sceNp2.warning("roomMemberBinAttrInternal: *0x%x", req->roomMemberBinAttrInternal);
		sceNp2.warning("roomMemberBinAttrInternalNum: %d", req->roomMemberBinAttrInternalNum);
		print_presence_data(&req->optData);
		sceNp2.warning("teamId: %d", req->teamId);

		for (u32 i = 0; i < req->roomMemberBinAttrInternalNum; i++)
			print_bin_attr(&req->roomMemberBinAttrInternal[i]);
	}

	void print_search_room(const SceNpMatching2SearchRoomRequest* req)
	{
		sceNp2.warning("SceNpMatching2SearchRoomRequest:");
		sceNp2.warning("option: 0x%x", req->option);
		sceNp2.warning("worldId: %d", req->worldId);
		sceNp2.warning("lobbyId: %lld", req->lobbyId);
		print_range_filter(&req->rangeFilter);
		sceNp2.warning("flagFilter: 0x%x", req->flagFilter);
		sceNp2.warning("flagAttr: 0x%x", req->flagAttr);
		sceNp2.warning("intFilter: *0x%x", req->intFilter);
		sceNp2.warning("intFilterNum: %d", req->intFilterNum);
		sceNp2.warning("binFilter: *0x%x", req->binFilter);
		sceNp2.warning("binFilterNum: %d", req->binFilterNum);
		sceNp2.warning("attrId: *0x%x", req->attrId);
		sceNp2.warning("attrIdNum: %d", req->attrIdNum);
	}

	void print_search_room_resp(const SceNpMatching2SearchRoomResponse* resp)
	{
		sceNp2.warning("SceNpMatching2SearchRoomResponse:");
		print_range(&resp->range);

		const SceNpMatching2RoomDataExternal *room_ptr = resp->roomDataExternal.get_ptr();
		for (u32 i = 0; i < resp->range.total; i++)
		{
			sceNp2.warning("SceNpMatching2SearchRoomResponse[%d]:", i);
			print_room_data_external(room_ptr);
			room_ptr = room_ptr->next.get_ptr();
		}
	}

	void print_room_member_data_internal(const SceNpMatching2RoomMemberDataInternal* member)
	{
		sceNp2.warning("SceNpMatching2RoomMemberDataInternal:");
		sceNp2.warning("next: *0x%x", member->next);
		sceNp2.warning("npId: %s", member->userInfo.npId.handle.data);
		sceNp2.warning("onlineName: %s", member->userInfo.onlineName->data);
		sceNp2.warning("avatarUrl: %s", member->userInfo.avatarUrl->data);
		sceNp2.warning("joinDate: %lld", member->joinDate.tick);
		sceNp2.warning("memberId: %d", member->memberId);
		sceNp2.warning("teamId: %d", member->teamId);
		sceNp2.warning("roomGroup: *0x%x", member->roomGroup);
		sceNp2.warning("natType: %d", member->natType);
		sceNp2.warning("flagAttr: 0x%x", member->flagAttr);
		sceNp2.warning("roomMemberBinAttrInternal: *0x%x", member->roomMemberBinAttrInternal);
		sceNp2.warning("roomMemberBinAttrInternalNum: %d", member->roomMemberBinAttrInternalNum);
		for (u32 i = 0; i < member->roomMemberBinAttrInternalNum; i++)
			print_member_bin_attr_internal(&member->roomMemberBinAttrInternal[i]);
	}

	void print_room_data_internal(const SceNpMatching2RoomDataInternal* room)
	{
		sceNp2.warning("SceNpMatching2RoomDataInternal:");
		sceNp2.warning("serverId: %d", room->serverId);
		sceNp2.warning("worldId: %d", room->worldId);
		sceNp2.warning("lobbyId: %lld", room->lobbyId);
		sceNp2.warning("roomId: %lld", room->roomId);
		sceNp2.warning("passwordSlotMask: %lld", room->passwordSlotMask);
		sceNp2.warning("maxSlot: %d", room->maxSlot);

		sceNp2.warning("members: *0x%x", room->memberList.members);
		auto cur_member = room->memberList.members;
		while (cur_member)
		{
			print_room_member_data_internal(cur_member.get_ptr());
			cur_member = cur_member->next;
		}
		sceNp2.warning("membersNum: %d", room->memberList.membersNum);
		sceNp2.warning("me: *0x%x", room->memberList.me);
		sceNp2.warning("owner: *0x%x", room->memberList.owner);

		sceNp2.warning("roomGroup: *0x%x", room->roomGroup);
		sceNp2.warning("roomGroupNum: %d", room->roomGroupNum);
		sceNp2.warning("flagAttr: 0x%x", room->flagAttr);
		sceNp2.warning("roomBinAttrInternal: *0x%x", room->roomBinAttrInternal);
		sceNp2.warning("roomBinAttrInternalNum: %d", room->roomBinAttrInternalNum);
		for (u32 i = 0; i < room->roomBinAttrInternalNum; i++)
			print_bin_attr_internal(&room->roomBinAttrInternal[i]);
	}

	void print_room_data_external(const SceNpMatching2RoomDataExternal* room)
	{
		sceNp2.warning("SceNpMatching2RoomDataExternal:");
		sceNp2.warning("next: *0x%x", room->next);
		sceNp2.warning("serverId: %d", room->serverId);
		sceNp2.warning("worldId: %d", room->worldId);
		sceNp2.warning("publicSlotNum: %d", room->publicSlotNum);
		sceNp2.warning("privateSlotNum: %d", room->privateSlotNum);
		sceNp2.warning("lobbyId: %d", room->lobbyId);
		sceNp2.warning("roomId: %d", room->roomId);
		sceNp2.warning("openPublicSlotNum: %d", room->openPublicSlotNum);
		sceNp2.warning("maxSlot: %d", room->maxSlot);
		sceNp2.warning("openPrivateSlotNum: %d", room->openPrivateSlotNum);
		sceNp2.warning("curMemberNum: %d", room->curMemberNum);
		sceNp2.warning("SceNpMatching2RoomPasswordSlotMask: 0x%x", room->passwordSlotMask);
		sceNp2.warning("owner: *0x%x", room->owner);

		if (room->owner)
			print_userinfo2(room->owner.get_ptr());

		sceNp2.warning("roomGroup: *0x%x", room->roomGroup);
		// TODO: print roomGroup
		sceNp2.warning("roomGroupNum: %d", room->roomGroupNum);
		sceNp2.warning("flagAttr: 0x%x", room->flagAttr);
		sceNp2.warning("roomSearchableIntAttrExternal: *0x%x", room->roomSearchableIntAttrExternal);
		sceNp2.warning("roomSearchableIntAttrExternalNum: %d", room->roomSearchableIntAttrExternalNum);
		// TODO: print roomSearchableIntAttrExternal
		sceNp2.warning("roomSearchableBinAttrExternal: *0x%x", room->roomSearchableBinAttrExternal);
		sceNp2.warning("roomSearchableBinAttrExternalNum: %d", room->roomSearchableBinAttrExternalNum);
		// TODO: print roomSearchableBinAttrExternal
		sceNp2.warning("roomBinAttrExternal: *0x%x", room->roomBinAttrExternal);
		sceNp2.warning("roomBinAttrExternalNum: %d", room->roomBinAttrExternalNum);
		// TODO: print roomBinAttrExternal
	}

	void print_create_room_resp(const SceNpMatching2CreateJoinRoomResponse* resp)
	{
		sceNp2.warning("SceNpMatching2CreateJoinRoomResponse:");
		sceNp2.warning("roomDataInternal: *0x%x", resp->roomDataInternal);
		if (resp->roomDataInternal)
			print_room_data_internal(resp->roomDataInternal.get_ptr());
	}

	void print_set_roomdata_ext_req(const SceNpMatching2SetRoomDataExternalRequest* req)
	{
		sceNp2.warning("SceNpMatching2SetRoomDataExternalRequest:");
		sceNp2.warning("roomId: %d", req->roomId);
		sceNp2.warning("roomSearchableIntAttrExternal: *0x%x", req->roomSearchableIntAttrExternal);
		sceNp2.warning("roomSearchableIntAttrExternalNum: %d", req->roomSearchableIntAttrExternalNum);
		sceNp2.warning("roomSearchableBinAttrExternal: *0x%x", req->roomSearchableBinAttrExternal);
		sceNp2.warning("roomSearchableBinAttrExternalNum: %d", req->roomSearchableBinAttrExternalNum);
		sceNp2.warning("roomBinAttrExternal: *0x%x", req->roomBinAttrExternal);
		sceNp2.warning("roomBinAttrExternalNum: %d", req->roomBinAttrExternalNum);
	}

	void print_set_roomdata_int_req(const SceNpMatching2SetRoomDataInternalRequest* req)
	{
		sceNp2.warning("SceNpMatching2SetRoomDataInternalRequest:");
		sceNp2.warning("roomId: %d", req->roomId);
		sceNp2.warning("flagFilter: 0x%x", req->flagFilter);
		sceNp2.warning("flagAttr: 0x%x", req->flagAttr);
		sceNp2.warning("roomBinAttrInternal: *0x%x", req->roomBinAttrInternal);
		sceNp2.warning("roomBinAttrInternalNum: %d", req->roomBinAttrInternalNum);
		sceNp2.warning("passwordConfig: *0x%x", req->passwordConfig);
		sceNp2.warning("passwordConfigNum: %d", req->passwordConfigNum);
		sceNp2.warning("passwordSlotMask: *0x%x", req->passwordSlotMask);
		sceNp2.warning("ownerPrivilegeRank: *0x%x", req->ownerPrivilegeRank);
		sceNp2.warning("ownerPrivilegeRankNum: %d", req->ownerPrivilegeRankNum);
	}

	void print_set_roommemberdata_int_req(const SceNpMatching2SetRoomMemberDataInternalRequest* req)
	{
		sceNp2.warning("SceNpMatching2SetRoomMemberDataInternalRequest:");
		sceNp2.warning("roomId: %d", req->roomId);
		sceNp2.warning("memberId: %d", req->memberId);
		sceNp2.warning("teamId: %d", req->teamId);
		sceNp2.warning("flagFilter: 0x%x", req->flagFilter);
		sceNp2.warning("flagAttr: 0x%x", req->flagAttr);
		sceNp2.warning("roomMemberBinAttrInternal: *0x%x", req->roomMemberBinAttrInternal);
		sceNp2.warning("roomMemberBinAttrInternalNum: %d", req->roomMemberBinAttrInternalNum);
		for (u32 i = 0; i < req->roomMemberBinAttrInternalNum; i++)
			print_bin_attr(&req->roomMemberBinAttrInternal[i]);
	}

	void print_get_roomdata_external_list_req(const SceNpMatching2GetRoomDataExternalListRequest* req)
	{
		sceNp2.warning("SceNpMatching2GetRoomDataExternalListRequest:");
		sceNp2.warning("roomId: *0x%x", req->roomId);
		sceNp2.warning("roomIdNum: %d", req->roomIdNum);
		for (u32 i = 0; i < req->roomIdNum; i++)
		{
			sceNp2.warning("RoomId[%d] = %d", i, req->roomId[i]);
		}
		sceNp2.warning("attrId: *0x%x", req->attrId);
		sceNp2.warning("attrIdNum: %d", req->attrIdNum);
		for (u32 i = 0; i < req->attrIdNum; i++)
		{
			sceNp2.warning("attrId[%d] = %d", i, req->attrId[i]);
		}
	}

	void print_get_roomdata_external_list_resp(const SceNpMatching2GetRoomDataExternalListResponse* resp)
	{
		sceNp2.warning("SceNpMatching2GetRoomDataExternalListResponse:");
		sceNp2.warning("roomDataExternal: *0x%x", resp->roomDataExternal);
		sceNp2.warning("roomDataExternalNum: %d", resp->roomDataExternalNum);

		const SceNpMatching2RoomDataExternal* cur_room = resp->roomDataExternal.get_ptr();

		for (u32 i = 0; i < resp->roomDataExternalNum; i++)
		{
			sceNp2.warning("SceNpMatching2GetRoomDataExternalListResponse[%d]:", i);
			print_room_data_external(cur_room);
			cur_room = cur_room->next.get_ptr();
		}
	}

	void print_SceNpBasicExtendedAttachmentData(const SceNpBasicExtendedAttachmentData* data)
	{
		sceNp.warning("SceNpBasicExtendedAttachmentData:");

		sceNp.warning("flags: 0x%x", data->flags);
		sceNp.warning("msgId: %d", data->msgId);
		sceNp.warning("SceNpBasicAttachmentData.id: %d", data->data.id);
		sceNp.warning("SceNpBasicAttachmentData.size: %d", data->data.size);
		sceNp.warning("userAction: %d", data->userAction);
		sceNp.warning("markedAsUsed: %d", data->markedAsUsed);
	}

} // namespace extra_nps
