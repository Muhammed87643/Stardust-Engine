#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <Utilities/Timer.h>


/**
 * Basic engine profiler
**/
namespace Stardust::Profiling {

	/**
	 * Statistics of an individual method run
	**/
	struct ProfileRun {
		double time;
		double fromStart;
	};

	/**
	 * Statistics of an individual method
	**/
	struct ProfileData {
		double minTime;
		double avgTime;
		double maxTime;
		double medianTime;

		std::vector<ProfileRun> runs;
		std::string method;
		std::vector<ProfileData> subProfiles;
	};

	class Profiler {
	public:
		/**
		 * Application profiler constructor. Name effects the formatted output.
		 * 
		 * @param name - Name by default is "APP"
		**/
		Profiler(std::string name = "APP");

		/**
		 * Begins profiling a method - sets internal state.
		**/
		auto beginProfileMethod() -> void;

		/**
		 * Ends profiling a method and collects statistics.
		**/
		auto endProfileMethod(std::string methodName) -> void;

		/**
		 * Outputs all profiled data to an output file.
		 * Also forces calculations for the entire data set for statistics.
		 * 
		 * @param fileName - Defaults to "stardust_profiler.log"
		**/
		auto outputStats(std::string fileName = "stardust_profiler.log") -> void;


	private:
		
		auto findMethod(std::string name) -> int;

		std::vector<ProfileData> methodData;
		Utilities::Timer t;
		Utilities::Timer subT;
		std::string profilerName;
	};


	/**
	 * Simple macro to profile a specific function
	**/
	#define SDE_PROFILE(pf, funcCall, funcName) pf.beginProfileMethod(); func; pf.endProfileMethod(funcName)
}
