//
// MenuPage.xaml.h
// Declaration of the MenuPage class
//

#pragma once

#include "Common\LayoutAwarePage.h" // Required by generated header
#include "MenuPage.g.h"

namespace Project
{
	/// <summary>
	/// A basic page that provides characteristics common to most applications.
	/// </summary>
	public ref class MenuPage sealed
	{
	public:
		MenuPage();

	protected:
		virtual void LoadState(Platform::Object^ navigationParameter,
			Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState) override;
		virtual void SaveState(Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState) override;
	private:
		void Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Button_Click_2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Button_Click_3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Button_Click_4(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
