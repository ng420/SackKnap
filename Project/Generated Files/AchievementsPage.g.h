﻿

#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class Image;
                ref class Button;
                ref class TextBlock;
            }
        }
    }
}

namespace Project
{
    partial ref class AchievementsPage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::Image^ IsUSubmitterImg;
        private: ::Windows::UI::Xaml::Controls::Image^ IsAllGoldImg;
        private: ::Windows::UI::Xaml::Controls::Image^ IsTimeUSavvyImg;
        private: ::Windows::UI::Xaml::Controls::Image^ isOnUSpreeImg;
        private: ::Windows::UI::Xaml::Controls::Image^ isCompleteText;
        private: ::Windows::UI::Xaml::Controls::Image^ isTimeSavvyImg;
        private: ::Windows::UI::Xaml::Controls::Image^ isOnSpreeImg;
        private: ::Windows::UI::Xaml::Controls::Button^ backButton;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ pageTitle;
    };
}

