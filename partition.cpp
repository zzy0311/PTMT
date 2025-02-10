#include "partition.hpp"

int getTimeConstraint(vector<event>& events, 
                        vector<tcons>& ts_purn,   //Growth Zone
                        vector<tcons>& ts_purn_repeat, //Boundary Zone
                        int delta,  //delta*l
                        int omega  //omega 
                        ) {
    
    int edge_num = events.size();
    int start_ts = events[0].first;//first->time
    omega*=delta;
    int end_ts = events[edge_num - 1].first;
    int ts_span = end_ts - start_ts;
    if(ts_span <= 0) { //
        cout << "timestamp not sort" << endl;
        return -1;
    }

    int low = 0, high = 0;
    int now_window = start_ts + omega;
    int index;
    for(int item = 0; item < edge_num; ++item) {
        if(events[item].first >(now_window - delta)) {
            high = item;
            while(item < edge_num - 1 && events[item].first <=now_window) {
                ++item;
            }
            if(item == edge_num - 1) {
                break;
            }
            if(item - low >= 2) {
                ts_purn.emplace_back(low, item);
            }
            if(item - high >= 2&&now_window + omega < end_ts) {
                ts_purn_repeat.emplace_back(high, item);
            }

            low = high;
            if(now_window + omega >= end_ts) {
             
                break;
            } else {
                now_window += omega;
            }
        }
    }

    if((edge_num - 1) - low >= 2) {
        ts_purn.emplace_back(low, edge_num - 1);
    }

    return ts_purn.size(); //window num
}

// vector<event> getEventsSubset(vector<event>& events, int start, int end) {
//     // 
//     if (start < 0 || end >= events.size() || start > end) {
//         throw out_of_range("Invalid start or end index");
//     }
//     auto startIter = events.begin() + start;
//     auto endIter = events.begin() + end + 1; // 

//     return vector<event>(startIter, endIter);
// }