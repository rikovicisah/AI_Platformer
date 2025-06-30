#pragma once
#include <vector>

class QAgent {
public:
    QAgent(int numStates, int numActions);

    int selectAction(int state);
    void update(int state, int action, float reward, int nextState);

    void setEpsilon(float e);
    void setLearningRate(float lr);
    void setDiscountFactor(float df);

private:
    std::vector<std::vector<float>> Q;
    float epsilon = 0.1f;
    float alpha = 0.1f;
    float gamma = 0.9f;
    int numActions;

    int randomAction();
    int bestAction(int state);
};
