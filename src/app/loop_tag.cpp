// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/loop_tag.h"

#include "doc/sprite.h"
#include "doc/frame_tag.h"

namespace app {

const char* kLoopTagName = "Loop";

doc::FrameTag* get_shortest_tag(const doc::Sprite* sprite, doc::frame_t frame)
{
  const doc::FrameTag* found = nullptr;
  for (const doc::FrameTag* tag : sprite->frameTags()) {
    if (frame >= tag->fromFrame() &&
        frame <= tag->toFrame()) {
      if (!found ||
          (tag->toFrame() - tag->fromFrame()) < (found->toFrame() - found->fromFrame())) {
        found = tag;
      }
    }
  }
  return const_cast<doc::FrameTag*>(found);
}

doc::FrameTag* get_loop_tag(doc::Sprite* sprite)
{
  // Get tag with special "Loop" name
  for (doc::FrameTag* tag : sprite->frameTags())
    if (tag->name() == kLoopTagName)
      return tag;

  return nullptr;
}

doc::FrameTag* create_loop_tag(doc::frame_t from, doc::frame_t to)
{
  doc::FrameTag* tag = new doc::FrameTag(from, to);
  tag->setName(kLoopTagName);
  return tag;
}

} // app
