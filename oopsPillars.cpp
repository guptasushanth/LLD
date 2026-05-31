#include <iostream>
#include <vector>

using namespace std;

// Abstraction
class AIModel {
public:
    virtual string generateResponse(string prompt) = 0;
    virtual ~AIModel() = default;
};

// Inheritance
class GPTModel : public AIModel {
public:
    string generateResponse(string prompt) override {
        return "GPT Response: " + prompt;
    }
};

class ClaudeModel : public AIModel {
public:
    string generateResponse(string prompt) override {
        return "Claude Response: " + prompt;
    }
};

class Agent {
private:
    string modelName; // Encapsulation

protected:
    AIModel* model;

public:
    Agent(string name, AIModel* model)
        : modelName(name), model(model) {}

    virtual void execute(string task) {
        cout << model->generateResponse(task) << endl;
    }

    string getModelName() {
        return modelName;
    }

    virtual ~Agent() = default;
};

// Inheritance
class CodingAgent : public Agent {
public:
    CodingAgent(string name, AIModel* model)
        : Agent(name, model) {}

    // Polymorphism
    void execute(string task) override {
        cout << "[Coding Agent] Solving: "
             << model->generateResponse(task)
             << endl;
    }
};

class ResearchAgent : public Agent {
public:
    ResearchAgent(string name, AIModel* model)
        : Agent(name, model) {}

    // Polymorphism
    void execute(string task) override {
        cout << "[Research Agent] Researching: "
             << model->generateResponse(task)
             << endl;
    }
};

int main() {
    AIModel* gpt = new GPTModel();
    AIModel* claude = new ClaudeModel();

    vector<Agent*> agents;

    agents.push_back(new CodingAgent("CodeGPT", gpt));
    agents.push_back(new ResearchAgent("ResearchClaude", claude));

    for (auto agent : agents) {
        agent->execute("How do I build an AI Agent?");
    }

    return 0;
}