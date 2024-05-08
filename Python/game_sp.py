from ursina import *

class LaberintoJuego(Entity):
    def __init__(self, size, maze):
        super().__init__()

        self.size = size
        self.maze = maze

        self.player = Player(self)
        self.create_maze()
        self.create_floor()

    def create_maze(self):
        for i in range(self.size):
            for j in range(self.size):
                if self.maze[i][j] == 1:
                    Wall(parent=self, position=(i - self.size / 2, 0, j - self.size / 2))
    
    def create_floor(self):
        floor = Entity(
            model='cube',
            color=color.gray,
            scale=(self.size, 0.1, self.size),
            position=(0, -0.5, 0),
            collider='box'
        )


class Player(Entity):
    def __init__(self, game):
        super().__init__(
            model='sphere',
            color=color.orange,
            scale=0.5,
            position=(0, 5, 0),
            collider='sphere',
            origin_y=-0.5
        )
        self.game = game
        self.gravity = -0.2  # Reducir la gravedad
        self.y_speed = 0.5  # Reducir la velocidad vertical

    def update(self):
        # Aplicar gravedad
        self.y_speed += self.gravity * time.dt
        self.y += self.y_speed * time.dt

        # Verificar colisiones con las paredes del laberinto
        hit_info = self.intersects()

        if hit_info.hit:
            self.y = hit_info.point.y
            self.y_speed = 0

        # Movimiento con las teclas
        if held_keys['a'] and self.x > -self.game.size / 2:
            self.x -= 1
        if held_keys['d'] and self.x < self.game.size / 2 - 1:
            self.x += 1
        if held_keys['w'] and self.z < self.game.size / 2 - 1:
            self.z += 1
        if held_keys['s'] and self.z > -self.game.size / 2:
            self.z -= 1

class Wall(Entity):
    def __init__(self, **kwargs):
        super().__init__(
            model='cube',
            color=color.white,
            scale=(1, 1, 1),
            collider='box',
            **kwargs
        )

class Sphere(Entity):
    def __init__(self, **kwargs):
        super().__init__(
            model='sphere',
            color=color.green,
            scale=0.5,
            collider='sphere',
            **kwargs
        )

# Tamaño del laberinto
GRID_SIZE = 10

# Definición del laberinto
laberinto = [
    [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 1, 1, 1, 0, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 1, 1, 1, 1, 1, 1, 1, 1, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 1, 1, 1, 1, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 1, 1, 1, 1, 1, 1, 0, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 1, 1, 1, 1, 1, 1, 1, 0, 0]
]

app = Ursina()
window.vsync = False

laberinto_juego = LaberintoJuego(GRID_SIZE, laberinto)
editor_camera = EditorCamera()
app.run()
