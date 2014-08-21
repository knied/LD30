//
//  MthIntegrate.h
//  Mth
//
//  Created by Kristof Niederholtmeyer on 20.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef Mth_MthIntegrate_h
#define Mth_MthIntegrate_h

////////////////////////////////////////////////////////////////////////////////

namespace Mth {
    
////////////////////////////////////////////////////////////////////////////////
    
    // Euler
    struct RK1 {
        template<class Context, class State, class Time>
        static State integrate(Context const& context, State const& state, Time dt, Time t) {
            return state + dt * evaluate(context, state, t);
        }
    }; // RK1
    
    // Runge Kutta 4th order
    struct RK4 {
        template<class Context, class State, class Time>
        static State integrate(Context const& context, State const& state, Time dt, Time t) {
            auto k1 = evaluate(context, state, t);
            auto k2 = evaluate(context, state + dt / 2 * k1, t + dt / 2);
            auto k3 = evaluate(context, state + dt / 2 * k2, t + dt / 2);
            auto k4 = evaluate(context, state + dt * k3, t + dt);
            
            return state + dt / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
        }
    }; // RK4
    
////////////////////////////////////////////////////////////////////////////////
    
} // Mth

////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////
