/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.
--*/
#pragma once
#include "../../inc/cppwinrt_utils.h"
#include "../types/inc/colorTable.hpp"

#include <DefaultSettings.h>
#include <conattrs.hpp>
#include "MySettings.g.h"

namespace winrt::SampleApp::implementation
{
    struct MySettings : MySettingsT<MySettings>
    {
        // --------------------------- Core Settings ---------------------------
        //  All of these settings are defined in ICoreSettings.

        // GetColorTableEntry needs to be implemented manually, to get a
        // particular value from the array.
        Microsoft::Terminal::Core::Color GetColorTableEntry(int32_t index) noexcept;
        void ColorTable(std::array<Microsoft::Terminal::Core::Color, 16> colors);
        std::array<Microsoft::Terminal::Core::Color, 16> ColorTable();

        INHERITABLE_SETTING(MySettings, til::color, DefaultForeground, DEFAULT_FOREGROUND);
        INHERITABLE_SETTING(MySettings, til::color, DefaultBackground, DEFAULT_BACKGROUND);
        INHERITABLE_SETTING(MySettings, til::color, SelectionBackground, DEFAULT_FOREGROUND);
        INHERITABLE_SETTING(MySettings, int32_t, HistorySize, DEFAULT_HISTORY_SIZE);
        INHERITABLE_SETTING(MySettings, int32_t, InitialRows, 30);
        INHERITABLE_SETTING(MySettings, int32_t, InitialCols, 80);

        INHERITABLE_SETTING(MySettings, bool, SnapOnInput, true);
        INHERITABLE_SETTING(MySettings, bool, AltGrAliasing, true);
        INHERITABLE_SETTING(MySettings, til::color, CursorColor, DEFAULT_CURSOR_COLOR);
        INHERITABLE_SETTING(MySettings, Microsoft::Terminal::Core::CursorStyle, CursorShape, Core::CursorStyle::Vintage);
        INHERITABLE_SETTING(MySettings, uint32_t, CursorHeight, DEFAULT_CURSOR_HEIGHT);
        INHERITABLE_SETTING(MySettings, hstring, WordDelimiters, DEFAULT_WORD_DELIMITERS);
        INHERITABLE_SETTING(MySettings, bool, CopyOnSelect, false);
        INHERITABLE_SETTING(MySettings, bool, FocusFollowMouse, false);
        INHERITABLE_SETTING(MySettings, bool, TrimBlockSelection, false);
        INHERITABLE_SETTING(MySettings, bool, DetectURLs, true);

        INHERITABLE_SETTING(MySettings, Windows::Foundation::IReference<Microsoft::Terminal::Core::Color>, TabColor, nullptr);

        // When set, StartingTabColor allows to create a terminal with a "sticky" tab color.
        // This color is prioritized above the TabColor (that is usually initialized based on profile settings).
        // Due to this prioritization, the tab color will be preserved upon settings reload
        // (even if the profile's tab color gets altered or removed).
        // This property is expected to be passed only once upon terminal creation.
        // TODO: to ensure that this property is not populated during settings reload,
        // we should consider moving this property to a separate interface,
        // passed to the terminal only upon creation.
        INHERITABLE_SETTING(MySettings, Windows::Foundation::IReference<Microsoft::Terminal::Core::Color>, StartingTabColor, nullptr);

        INHERITABLE_SETTING(MySettings, bool, IntenseIsBright);

        INHERITABLE_SETTING(MySettings, bool, AdjustIndistinguishableColors);

        // ------------------------ End of Core Settings -----------------------

        INHERITABLE_SETTING(MySettings, hstring, ProfileName);
        INHERITABLE_SETTING(MySettings, hstring, ProfileSource);

        INHERITABLE_SETTING(MySettings, bool, UseAcrylic, true);
        INHERITABLE_SETTING(MySettings, double, Opacity, UseAcrylic() ? 0.5 : 1.0);
        INHERITABLE_SETTING(MySettings, hstring, Padding, DEFAULT_PADDING);
        INHERITABLE_SETTING(MySettings, hstring, FontFace, DEFAULT_FONT_FACE);
        INHERITABLE_SETTING(MySettings, int32_t, FontSize, DEFAULT_FONT_SIZE);

        INHERITABLE_SETTING(MySettings, winrt::Windows::UI::Text::FontWeight, FontWeight);
        INHERITABLE_SETTING(MySettings, IFontAxesMap, FontAxes);
        INHERITABLE_SETTING(MySettings, IFontFeatureMap, FontFeatures);

        INHERITABLE_SETTING(MySettings, Model::ColorScheme, AppliedColorScheme);
        INHERITABLE_SETTING(MySettings, hstring, BackgroundImage);
        INHERITABLE_SETTING(MySettings, double, BackgroundImageOpacity, 1.0);

        INHERITABLE_SETTING(MySettings, winrt::Windows::UI::Xaml::Media::Stretch, BackgroundImageStretchMode, winrt::Windows::UI::Xaml::Media::Stretch::UniformToFill);
        INHERITABLE_SETTING(MySettings, winrt::Windows::UI::Xaml::HorizontalAlignment, BackgroundImageHorizontalAlignment, winrt::Windows::UI::Xaml::HorizontalAlignment::Center);
        INHERITABLE_SETTING(MySettings, winrt::Windows::UI::Xaml::VerticalAlignment, BackgroundImageVerticalAlignment, winrt::Windows::UI::Xaml::VerticalAlignment::Center);

        INHERITABLE_SETTING(MySettings, Microsoft::Terminal::Control::IKeyBindings, KeyBindings, nullptr);

        INHERITABLE_SETTING(MySettings, hstring, Commandline);
        INHERITABLE_SETTING(MySettings, hstring, StartingDirectory);
        INHERITABLE_SETTING(MySettings, hstring, StartingTitle);
        INHERITABLE_SETTING(MySettings, bool, SuppressApplicationTitle);
        INHERITABLE_SETTING(MySettings, hstring, EnvironmentVariables);

        INHERITABLE_SETTING(MySettings, Microsoft::Terminal::Control::ScrollbarState, ScrollState, Microsoft::Terminal::Control::ScrollbarState::Visible);
        INHERITABLE_SETTING(MySettings, bool, UseAtlasEngine, false);

        INHERITABLE_SETTING(MySettings, Microsoft::Terminal::Control::TextAntialiasingMode, AntialiasingMode, Microsoft::Terminal::Control::TextAntialiasingMode::Grayscale);

        INHERITABLE_SETTING(MySettings, bool, RetroTerminalEffect, false);
        INHERITABLE_SETTING(MySettings, bool, ForceFullRepaintRendering, false);
        INHERITABLE_SETTING(MySettings, bool, SoftwareRendering, false);
        INHERITABLE_SETTING(MySettings, bool, ForceVTInput, false);

        INHERITABLE_SETTING(MySettings, hstring, PixelShaderPath);
        INHERITABLE_SETTING(MySettings, bool, IntenseIsBold);
    }
}

namespace winrt::SampleApp::factory_implementation
{
    BASIC_FACTORY(MySettings);
}
