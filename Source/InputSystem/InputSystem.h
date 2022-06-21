#pragma once

#include "../MessageSystem/MessageSystemNode.h"
#include "Input.h"

class InputSystem : public MessageSystemNode {
public:
	// Constructor
	InputSystem(MessageSystem* messageSystem) : MessageSystemNode(messageSystem) {};
	// Destructor
	~InputSystem() {};

	void ProcessKeyboardInput(KeyboardInput keyboardInput);

private:
	// Override void provided by MessageSystemNode
	virtual void onNotify(Message message) override;
};