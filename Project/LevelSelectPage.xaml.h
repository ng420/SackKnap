//
// LevelSelectPage.xaml.h
// Declaration of the LevelSelectPage class
//

#pragma once

#include "Common\LayoutAwarePage.h" // Required by generated header
#include "LevelSelectPage.g.h"

namespace Project
{
	/// <summary>
	/// A basic page that provides characteristics common to most applications.
	/// </summary>
	[Windows::UI::Xaml::Data::Bindable]
	public ref class Levels sealed
	{
	public:
		property Platform::String^ BestTime;
		property Platform::String^ BestMedal;
		property Platform::String^ number;
	};
	
	public ref class LevelSelectPage sealed
	{
	public:
		LevelSelectPage();
		int ConvertToInt(Platform::String^ initial);
		Platform::String^ ConvertToPString(int val);
		property Windows::Foundation::Collections::IVector<Levels^>^ levels
        {
			Windows::Foundation::Collections::IVector<Levels^>^ get() {return levelsvector; }
        }

	protected:
		virtual void LoadState(Platform::Object^ navigationParameter,
			Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState) override;
		virtual void SaveState(Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState) override;
		
	private:
		void PageLoadedHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		Windows::Foundation::Collections::IVector<Levels^>^ levelsvector;

		void ItemListView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void AddLevel(Platform::String^ number,Platform::String^ BestTime,Platform::String^ BestMedal)
		{
			Levels^ _lvl=ref new Levels();_lvl->number=number;
			_lvl->BestMedal=BestMedal;
			_lvl->BestTime=BestTime;
			levels->Append(_lvl);
		}
		void CloseSettingsPopupClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void StartSettingsPopupClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
