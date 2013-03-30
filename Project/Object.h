#pragma once

#include <collection.h>
#include "pch.h"

namespace Project
{
	[Windows::UI::Xaml::Data::Bindable]
	public ref class Objects sealed
		{
		public:
			property Platform::String^ profit;
			property Platform::String^ weight;
			//Objects::Objects(int _profit,int _weight){ profit=_profit;weight=_weight;}
			//void setValues(int p,int w){profit=p;weight=w;}
		};
	[Windows::UI::Xaml::Data::Bindable]
	public ref class ObjectsGroup sealed
	{
		private:
			Windows::Foundation::Collections::IVector<Objects^>^ group;
	public:
		property Platform::String^ Time;
		property Platform::String^ Profit;
		property Platform::String^ Capacity;
		property Platform::String^ Weight;
		property Platform::String^ Gold;
		property Platform::String^ Silver;
		property Platform::String^ Bronze;
		property Platform::String^ Minimum;
		ObjectsGroup()
		{
			group = ref new Platform::Collections::Vector<Objects^>();
		}
		property Windows::Foundation::Collections::IVector<Objects^>^ Items
        {
			Windows::Foundation::Collections::IVector<Objects^>^ get() {return group; }
        }

	};

	
}
