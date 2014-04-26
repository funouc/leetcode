/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
	vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
		vector<Interval> v;
		Interval inv;
		if(intervals.empty()){
			v.push_back(newInterval);
			return v;
		}
		int a,b;
	//	b=intervals.size();
		int i=0;
		for(i=0;i<intervals.size();i++){
			if(intervals[i].end<newInterval.start)
				continue;
			else{
				if(newInterval.start>=intervals[i].start)
					a=i;
				else
					a=i;
				break;
			}
		}
		if(i==intervals.size()){
			v=intervals;
			v.push_back(newInterval); 
			return v;
		}
		for(i=intervals.size()-1;i>=0;i--){
			if(intervals[i].start>newInterval.end)
				continue;
			else{
				b=i;
				break;
			}
		}
		if(i==-1){
			v.push_back(newInterval);
			for(i=0;i<intervals.size();i++)
				v.push_back(intervals[i]);
			return v;
		}
		for(i=0;i<a;i++)
			v.push_back(intervals[i]);
		if(newInterval.start<=intervals[a].start){
			inv.start=newInterval.start;
			if(newInterval.end>=intervals[b].end)
				inv.end=newInterval.end;
			else
				inv.end=intervals[b].end;
		}
		else{
			inv.start=intervals[a].start;
			if(newInterval.end>=intervals[b].end)
				inv.end=newInterval.end;
			else
				inv.end=intervals[b].end;
		}
		v.push_back(inv);
		for(i=b+1;i<intervals.size();i++)
			v.push_back(intervals[i]);
		return v;
	}
};
