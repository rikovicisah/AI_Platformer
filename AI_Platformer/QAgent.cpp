#include "QAgent.h"
#include <random>
#include <algorithm>

QAgent::QAgent(int numStates, int numActions)
    : numActions(numActions), Q(numStates, std::vector<float>(numActions, 0.0f)) {
}

int QAgent::selectAction(int state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    if (dist(gen) < epsilon)
        return randomAction();
    else
        return bestAction(state);
}

void QAgent::update(int state, int action, float reward, int nextState) {
    float maxQNext = *std::max_element(Q[nextState].begin(), Q[nextState].end());
    Q[state][action] += alpha * (reward + gamma * maxQNext - Q[state][action]);
}

int QAgent::randomAction() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, numActions - 1);
    return dist(gen);
}

int QAgent::bestAction(int state) {
    return std::distance(Q[state].begin(),
        std::max_element(Q[state].begin(), Q[state].end()));
}

void QAgent::setEpsilon(float e) { epsilon = e; }
void QAgent::setLearningRate(float lr) { alpha = lr; }
void QAgent::setDiscountFactor(float df) { gamma = df; }
