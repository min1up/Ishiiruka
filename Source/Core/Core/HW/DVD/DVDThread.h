// Copyright 2015 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include <vector>

#include "Common/CommonTypes.h"

class PointerWrap;
namespace DiscIO
{
struct Partition;
}
namespace DVDInterface
{
enum class ReplyType : u32;
}
namespace DiscIO
{
enum class Platform;
class IVolume;
}
namespace IOS
{
namespace ES
{
class TMDReader;
class TicketReader;
}
}

namespace DVDThread
{
void Start();
void Stop();
void DoState(PointerWrap& p);

void SetDisc(std::unique_ptr<DiscIO::IVolume> disc);
bool HasDisc();

DiscIO::Platform GetDiscType();
IOS::ES::TMDReader GetTMD(const DiscIO::Partition& partition);
IOS::ES::TicketReader GetTicket(const DiscIO::Partition& partition);
// If a disc is inserted and its title ID is equal to the title_id argument, returns true and
// calls SConfig::SetRunningGameMetadata(IVolume&, Partition&). Otherwise, returns false.
bool UpdateRunningGameMetadata(const DiscIO::Partition& partition, u64 title_id);
// If a disc is inserted, returns true and calls
// SConfig::SetRunningGameMetadata(IVolume&, Partition&). Otherwise, returns false.
bool UpdateRunningGameMetadata(const DiscIO::Partition& partition);

void StartRead(u64 dvd_offset, u32 length, const DiscIO::Partition& partition,
  DVDInterface::ReplyType reply_type, s64 ticks_until_completion);
void StartReadToEmulatedRAM(u32 output_address, u64 dvd_offset, u32 length,
  const DiscIO::Partition& partition, DVDInterface::ReplyType reply_type,
  s64 ticks_until_completion);
}