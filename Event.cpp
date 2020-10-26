#include "Event.h"
#include "NetworkGraph.h"
#include "Graph.cpp"
#include <algorithm>

float Event::recountEarliestTime(NetworkGraph* owner) {
	vector<string> lastEvents = vector<string>();
	owner->getLastVertices(this->name(), &lastEvents);
	if (!lastEvents.size())
		this->earliestTime = 0;
	else {
		vector<Event*> lastRealEvents = vector<Event*>();
		owner->getRealVertices(&lastEvents, &lastRealEvents);
		auto& largestWayEvent = *max_element(lastRealEvents.begin(), lastRealEvents.end(),
			[owner, this](Event* eventA, Event* eventB) {
				return eventA->getEarliestTime() + owner->getWeight(eventA->name(), this->name()) <
					eventB->getEarliestTime() + owner->getWeight(eventB->name(), this->name());
			});
		this->earliestTime = largestWayEvent->earliestTime + owner->getWeight(largestWayEvent->name(), this->name());
	}
	return this->earliestTime;
}

float Event::recountLatestTime(NetworkGraph* owner) {
	vector<string> nextEvents = vector<string>();
	owner->getNextVertices(this->name(), &nextEvents);
	if (!nextEvents.size())
		this->latestTime = this->earliestTime;
	else {
		vector<Event*> nextRealEvents = vector<Event*>();
		owner->getRealVertices(&nextEvents, &nextRealEvents);
		auto& shortestWayEvent = *min_element(nextRealEvents.begin(), nextRealEvents.end(),
			[owner, this](Event* eventA, Event* eventB) {
				return eventA->getLatestTime() - owner->getWeight(this->name(), eventA->name()) <
					eventB->getLatestTime() - owner->getWeight(this->name(), eventB->name());
			});
		this->latestTime = shortestWayEvent->latestTime - owner->getWeight(this->name(), shortestWayEvent->name());
	}
	return this->latestTime;
}

float Event::getEarliestTime() {
	return earliestTime;
}

float Event::getLatestTime() {
	return latestTime;
}
