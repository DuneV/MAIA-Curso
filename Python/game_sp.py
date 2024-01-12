from ursina import *
import serial 

#esp32 = serial.Serial(port='COM4', baudrate=115200, timeout=.1) 


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
            position=(0, 5, 0),  # Ajustar la posición inicial para evitar colisiones inmediatas
            collider='sphere',
            origin_y=-0.5  # Ajustar el origen para que la esfera ruede correctamente
        )
        self.game = game
        self.gravity = -0.5  # Configurar la gravedad
        self.y_speed = 0

    def update(self):
        # Aplicar gravedad
        self.y_speed += self.gravity * time.dt
        self.y += self.y_speed * time.dt

        # Verificar colisiones con las paredes del laberinto
        hit_info = self.intersects()

        if hit_info.hit:
            # print(hit_info.point.y)
            self.y = hit_info.point.y
            self.y_speed = 0

        # Movimiento con las teclas / esp32
        def read_port(x): 
            if esp32.in_waiting:
                packet = esp32.readline()
                time.sleep(0.05) 
                return packet.decode('utf').rstrip('\n')
            else:
                return ('WOI')
        
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

# Definición del laberinto (0 representa espacio libre, 1 representa pared)
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
# Agregar la cámara de editor para mover la perspectiva con el clic izquierdo
editor_camera = EditorCamera()
app.run()
