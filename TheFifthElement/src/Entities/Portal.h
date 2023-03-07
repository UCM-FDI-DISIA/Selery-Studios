class Portal : public Entity
{
private:
	Vector2D portalPosition_{ 100, 400 };
	float portalWidth_ = 290, portalHeight_ = 192, portalRotation_ = 1,portalVel=0;
	Texture* t;

	Transform* tr;
	Transform* trPlayer_;
	PlayerTD* player_;
	CheckCollision* ch;
	int nframes = 1;
	int elementsCollected = 0;
public:
	~Portal() {}

	void update() {}

	void elementEarned(); // Metodo que se usará cuando se derrote un jefe y se recoja su elemento

	void Teleport(Vector2D newPlayerPos);

	Portal(PlayerTD* player);

};

