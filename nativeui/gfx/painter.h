// Copyright 2016 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#ifndef NATIVEUI_GFX_PAINTER_H_
#define NATIVEUI_GFX_PAINTER_H_

#include <memory>

#include "nativeui/gfx/color.h"
#include "nativeui/gfx/font.h"
#include "nativeui/gfx/geometry/rect.h"
#include "nativeui/types.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

namespace nu {

class Pen;

// The interface for painting on canvas or window.
class Painter {
 public:
#if defined(OS_WIN)
  // Create a painter from HDC.
  static std::unique_ptr<Painter> CreateFromHDC(HDC dc);
#endif

  virtual ~Painter() = default;

  enum {
    // Specifies the alignment for text rendered with the DrawString method.
    TextAlignLeft   = 1 << 0,
    TextAlignCenter = 1 << 1,
    TextAlignRight  = 1 << 2,
  };

  // How the clip rect is combined with current one.
  enum class CombineMode {
    Replace,
    Intersect,
    Union,
    Exclude,
  };

  // Save/Restore current state.
  virtual void Save() = 0;
  virtual void Restore() = 0;

  // Applies |rect| to the current clip using the specified region |op|.
  virtual void ClipRect(const Rect& rect,
                        CombineMode mode = CombineMode::Replace) = 0;

  // The origin offset of the painting.
  virtual void Translate(const Vector2d& offset) = 0;

  // Draws a single pixel |rect| in the specified region with |color|.
  virtual void DrawRect(const Rect& rect, Color color) = 0;

  // Draws the given |rect| with the |pen|.
  virtual void DrawRect(const Rect& rect, Pen* pen) = 0;

  // Fills |rect| with |color|.
  virtual void FillRect(const Rect& rect, Color color) = 0;

  // Draws text with the specified color, fonts and location. The text is
  // aligned to the left, vertically centered, clipped to the region. If the
  // text is too big, it is truncated and '...' is added to the end.
  void DrawString(const String& text, Font font, Color color, const Rect& rect);

  // Draws text with the specified color, fonts and location. The last argument
  // specifies flags for how the text should be rendered.
  virtual void DrawStringWithFlags(const String& text,
                                   Font font,
                                   Color color,
                                   const Rect& rect,
                                   int flags) = 0;

 protected:
  Painter() = default;

 private:
  DISALLOW_COPY_AND_ASSIGN(Painter);
};

}  // namespace nu

#endif  // NATIVEUI_GFX_PAINTER_H_