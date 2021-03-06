﻿//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once
#include "MainPage.g.h"
#include "Object.h"
#include <list>
#include <vector>
#include <map>

namespace Project
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		
	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private: 
		int w,p;
		bool IsPaused;
		int Level;
void PageLoadedHandler(Platform::Object^ sender,
          Windows::UI::Xaml::RoutedEventArgs^ e);
		ObjectsGroup^ ObjGrp;
		int HighestLevelReached;
		Windows::Storage::ApplicationDataContainer^ localSettings;
		Platform::Array<int>^ medals;
		Platform::Array<Platform::String^>^times;
		std::list<int> l;
		std::list<int>::iterator lit;
		Platform::Collections::Vector<Objects^>^ ob;
		void ItemView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		Platform::String^ conv(Platform::String^ S1,Platform::String^ S2);
		void InitializeObjects();
		void AddObject(Platform::String^ profit,Platform::String^ weight)
		{
			Objects^ _obj1=ref new Objects();_obj1->profit=profit;
			_obj1->weight=weight;
			ObjGrp->Items->Append(_obj1);
		}
		void ObjectCreator(int t);
	public:
		void AnalyzeObjects();
		bool isTimeLesser(Platform::String^ Time1,Platform::String^ Time2);
		void StartTimerAndRegisterHandler();
		void OnTick(Object^ sender,Object^ e);
		void ProfitEval(unsigned int i);
		void Initialize();
		int ConvertToInt(Platform::String^ initial);
		Platform::String^ ConvertToPString(int val);
	private:
		void Submit(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void GoBack(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
