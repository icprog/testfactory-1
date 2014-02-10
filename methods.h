
namespace Tests
{
	using namespace ToBeDone;
	template <> Positive<ContainerType>::operator const bool () 
	{
		cout<<"Testing "<<name<<endl;
		TbdBase& tbd(main); TbdBase& me(*this);
		me=tbd;
		sort(begin(),end());
		const bool success(main(*this));
		return success;
	}

	template <> Negative<ContainerType>::operator const bool () 
	{
		cout<<"Testing "<<name<<endl;
		TbdBase& tbd(main); TbdBase& me(*this);
		me=tbd;
		// Just make sure the test result is not equal to the sorted results
		for (iterator it=begin();it!=end();it++) (*it)+=(rand()%5);
		const bool success(main(*this,false));  // expected to fail
		return success;
	}

	template <> Bubble<ContainerType>::operator const bool () 
	{
		cout<<"Testing "<<name<<endl;
		TbdBase& _tbd(main); 
		TbdBase& _me(*this);
		_me=_tbd;
		Tbd<TT>& tbd(static_cast<Tbd<TT>&>(_tbd));
		Tbd<TT>& me(static_cast<Tbd<TT>&>(_me));
		int times(size()-1);
		while (times)
		{
			for (int j=0;j<(times);j++)
				if (me[j]>me[j+1]) 
					swap<KeyType>(j,j+1);
			times--;
		}
		const bool success(main(*this));
		return success;
	}

	template <> Insertion<ContainerType>::operator const bool () 
	{
		cout<<"Testing "<<name<<endl;
		TbdBase& _tbd(main); 
		TbdBase& _me(*this);
		_me=_tbd;
		Tbd<TT>& tbd(static_cast<Tbd<TT>&>(_tbd));
		Tbd<TT>& me(static_cast<Tbd<TT>&>(_me));

		for (int i=1; i<size(); i++)
		{
			int j=i;
			while ((j>0) and (me[j-1] > me[j]) )
			{
				swap<KeyType>(j,j-1);
				--j;
			}
		}

		const bool success(main(*this,true));
		return success;
	}

	template <> Selection<ContainerType>::operator const bool () 
	{
		cout<<"Testing "<<name<<endl;
		TbdBase& _tbd(main); 
		TbdBase& _me(*this);
		_me=_tbd;
		Tbd<TT>& tbd(static_cast<Tbd<TT>&>(_tbd));
		Tbd<TT>& me(static_cast<Tbd<TT>&>(_me));

		int split(size());
		while (split>0)
		{
			pair<KeyType,int> selection(me[0],0);
			for (int j=0;j<split;j++)
				if (me[j]>=selection.first) {selection.first=me[j]; selection.second=j;}
			swap<KeyType>(selection.second,split-1);
			--split;
		}
		const bool success(main(*this));
		return success;
	}
} // Tests

namespace ToBeDone
{
	template <> TbdBase& Tbd<ContainerType>::operator=(TbdBase& b) 
	{
		Tbd& you(static_cast<Tbd&>(b));
		tt& me(*this);
		me=you;
		return *this;
	}
} // namespace

