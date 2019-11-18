#ifndef PLAYER_DESCRIPTOR_H
#define PLAYER_DESCRIPTOR_H

struct PlayerDescriptor {
	int globalId;
	int playerId;
	bool isBot;

	PlayerDescriptor() : globalId(-1),
						playerId(-1),
						isBot(false) {}

};

#endif // PLAYER_DESCRIPTOR_H
