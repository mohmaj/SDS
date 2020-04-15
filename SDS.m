clear
% search space (ss); target text (model); population size (N)
ss = 'try to find sds in this sentence'; 
model = 'sds';
N = 10; maxIter = 30;

% INITIALISE AGENTS
hypo = randi([1 length(ss)-length(model)],1,N) ;
status = false(1,N);

for itr=1:maxIter
	activeAgents = 0;
	% TEST PHASE
	for i=1:N
		% PICK A MICROFEATURE TO PARTIALLY EVALUATE HYPOTHSIS
		microFeature = randi([1 length(model)]); 
		if ss( hypo(i)+microFeature ) == model(microFeature) 
			status(i) = true;
			activeAgents = activeAgents+1;
		else 
			status(i) = false;
		end		
	end 

	% DIFFUSION PHASE
	for i=1:N
		if status(i) == false % INACTIVE AGENT
			rand = randi([1 N]); % PICK RANDOM AGENT TO COMMUNICATE
			if status(rand) == true % SHARE HYPOTHESIS
				hypo(i) = hypo(rand); 
			else % PICK A RANDOM HYPOTHSIS
				hypo(i) = randi([1 length(ss)-length(model)]);
			end
		else % ACTIVE AGENT
			microFeature = randi([1 length(model)]); % PICK MICROFEATURE
			if ss( hypo(i)+microFeature ) == model(microFeature)  
				status(i) = true;
			else 
				status(i) = false;
			end
		end
	end
	activityPercentage = activeAgents * 100 / N;
	% DISPLAYING ACTIVITY PERCENTAGE AND THE FIRST AGENT'S HYPOTHESIS
	disp(['Active agents: ' num2str(activityPercentage) '%  ... found: ' ss(hypo(1):length(model))])
end
