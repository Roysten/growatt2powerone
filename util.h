#pragma once

#ifdef TRACE
#define TRACE_FN() do { Serial.print("TRACE "); Serial.println(__func__); } while (false)
#else
#define TRACE_FN() do {} while (false)
#endif

