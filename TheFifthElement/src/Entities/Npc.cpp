#include "Npc.h"
Npc::Npc(PlayerTD* player, Vector2D NpcPosition_, Texture* t, int a) : Entity() {
	tr = addComponent<Transform>(TRANSFORM_H, NpcPosition_, NpcWidth_, NpcHeight_, NpcRotation_, npcSpeed, nframes, matrix_);
	//referencia al texture y al transform
	fila_ = 0;
	addComponent<Image>(IMAGE_H, t, nframes, nframes, fila_, NPC_WIDTH, NPC_HEIGHT);
	player_ = player;
	ch = addComponent<CheckCollision>(CHECKCOLLISION_H, player_, a);
	addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), NpcHeight_, NpcWidth_ / nframes);
}