class AppState {
    public:
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void handleInput() = 0;
        virtual ~AppState() = default;
};