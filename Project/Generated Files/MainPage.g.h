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
                ref class Grid;
                ref class GridView;
                ref class TextBlock;
            }
        }
    }
}

namespace Project
{
    partial ref class MainPage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::Grid^ Grid0;
        private: ::Windows::UI::Xaml::Controls::Grid^ Grid1;
        private: ::Windows::UI::Xaml::Controls::Grid^ grid2;
        private: ::Windows::UI::Xaml::Controls::GridView^ ItemListView;
        private: ::Windows::UI::Xaml::Controls::Grid^ Grid1B;
        private: ::Windows::UI::Xaml::Controls::Grid^ Grid1C;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ TitleText;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Result;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Capacity;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ WeightBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ ProfitBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Timer;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Minimum;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Bronze;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Silver;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Gold;
    };
}

