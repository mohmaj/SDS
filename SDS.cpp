#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
using namespace std;

float r() { // GENERATE RANODM NUMBER IN RANGE [0, 1)
	return (float) rand() / (RAND_MAX); 
}

int main() {
	srand(time(NULL)); // TO GENERATE DIFFERENRT RANDOM NUMBERS
	string ss = "try to find sds in this sentence"; // SEARCH SPACE
	string model = "sds"; // TARGET TEXT
	int N = 10; int maxIter = 30; int hypo[N]; bool status[N];
	
	// INITIALISE AGENTS
	for (int i=0; i<N; i++) {
		hypo[i] = r()*(ss.length() - model.length());
		status[i] = false;
	}
	
	// MAIN LOOP
	for (int itr=0; itr < maxIter; itr++) {
		int activeAgents = 0;
		// TEST PHASE
		for (int i=0; i<N; i++) {
			// PICK A MICROFEATURE TO PARTIALLY EVALUATE HYPOTHSIS
			int microFeature = r()*model.length(); 
			if (ss[ hypo[i]+microFeature ] == model[microFeature] ) {
				status[i] = true;
				activeAgents++;
			}
			else 
				status[i] = false;
		}
		// DIFFUSION PHASE
		for (int i=0; i<N; i++) {
			if (status[i] == false){ // INACTIVE AGENT
				int rand = r()*N; // PICK RANDOM AGENT TO COMMUNICATE
				if (status[rand] == true) // SHARE HYPOTHESIS
					hypo[i] = hypo[rand]; 
				else // PICK A RANDOM HYPOTHSIS
					hypo[i] = r()*(ss.length() - model.length());
			}
			else { // ACTIVE AGENT
				int microFeature = r()*model.length(); // PICK MICROFEATURE
				if (ss[ hypo[i]+microFeature ] == model[microFeature] ) 
					status[i] = true;
				else 
					status[i] = false;
			}
		}
		int activityPercentage = activeAgents * 100 / N;
		// DISPLAYING ACTIVITY PERCENTAGE AND THE FIRST AGENT'S HYPOTHESIS
		cout << "Active agents:" << activityPercentage << "%\t  ... found: " << ss.substr(hypo[0],model.length()) << endl;
	}	
	return 0;
}
