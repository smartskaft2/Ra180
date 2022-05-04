#pragma once

#include <iostream>
#include <functional>
#include <array>

namespace Ra180 {

   enum class KeyCode : unsigned int
   {
       _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
       A , B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Å, Ä, Ö,

       ArrowUp, ArrowDown, ArrowLeft, ArrowRight,

       ControlLeft, ControlRight, ShiftLeft, ShiftRight,

       Tab,
       Pause,
       Return,
       Escape, 

       Insert,
       Delete,
       Home,
       End,
       PageUp,
       PageDown,

       NumPad_0, NumPad_1, NumPad_2, NumPad_3, NumPad_4, NumPad_5, NumPad_6, NumPad_7, NumPad_8, NumPad_9,

       NumPad_Decimal, NumPad_Add, NumPad_Subtract, NumPad_Multiply, NumPad_Divide, NumPad_NumLock,

       // Must be last of master values!
       Count,

       NumPad_Return = Return,
   };

   std::ostream& writeSupportedKeys(std::ostream& os, const std::function<std::ostream& (std::ostream&, const KeyCode)> appendLineCallback = nullptr);

   constexpr std::array<KeyCode, static_cast<int>(KeyCode::Count)> SupportedKeysCodes()
   {
       std::array<KeyCode, static_cast<int>(KeyCode::Count)> supportedKeys;
       for (int k{}; k < supportedKeys.size(); ++k)
       {
           supportedKeys[k] = static_cast<KeyCode>(k);
       }
       return supportedKeys;
   }

} // namespace Ra180

std::ostream& operator<<(std::ostream& os, const Ra180::KeyCode keyCode);

