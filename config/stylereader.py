from . import basereader
from data import graphics
from data.config import style

class YamlStyleReader(basereader.BaseYamlReader):
    """ Yaml reader for style types.

    Constants:
    DEFAULT
    HEIGHT
    IMAGE
    IMAGES
    MAP
    MAPPING
    MAPPINGS
    NAME
    NAMESPACE
    PATH
    SPRITE
    SPRITES
    TILE_X
    TILE_Y
    TO
    WIDTH
    X
    Y
    """

    DEFAULT = 'default'
    HEIGHT = 'height'
    IMAGE = 'image'
    IMAGES = 'images'
    MAP = 'map'
    MAPPING = 'mapping'
    MAPPINGS = 'mappings'
    NAME = 'name'
    NAMESPACE = 'namespace'
    PATH = 'path'
    SPRITE = 'sprite'
    SPRITES = 'sprites'
    TILE_X = 'tile_x'
    TILE_Y = 'tile_y'
    TO = 'to'
    WIDTH = 'width'
    X = 'x'
    Y = 'y'

    def parse(self, root, data):
        """ Parse the style structure. Writes the parsed information into the
        data object. """
        namespace = self.read_req_string(root, self.NAMESPACE)

        data.graphics.tile_x = self.read_req_int(root, self.TILE_X)
        data.graphics.tile_y = self.read_req_int(root, self.TILE_Y)

        if self.has(root, self.IMAGES):
            self.__images(namespace, root, data)
        if self.has(root, self.MAPPINGS):
            self.__mappings(namespace, root, data)
        if self.has(root, self.SPRITES):
            self.__sprites(namespace, root, data)

    def __images(self, namespace, root, data):
        """ Parse images. """
        images = self.read_req_object(root, self.IMAGES)
        namespace_list = [namespace, self.read_req_string(images, self.NAMESPACE)]

        for image in self.read_object(images, self.IMAGE, []):
            name = self.read_req_string(image, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            path = self.read_req_string(image, self.PATH)
            data.config.style.images[id] = path

    def __mappings(self, namespace, root, data):
        """ Parse mappings. """
        mappings = self.read_req_object(root, self.MAPPINGS)
        data.config.style.default_mapping = self.read_string(mappings, self.DEFAULT, '')

        for mapping in self.read_object(mappings, self.MAPPING, []):
            map = self.read_req_string(mapping, self.MAP)
            to = self.read_req_string(mapping, self.TO)
            data.config.style.mappings[map] = to

    def __sprites(self, namespace, root, data):
        """ Parse sprites. """
        sprites = self.read_req_object(root, self.SPRITES)
        namespace_list = [namespace, self.read_req_string(sprites, self.NAMESPACE)]

        default_image = self.read_string(sprites, self.IMAGE, None)
        default_width = self.read_int(sprites, self.WIDTH, None)
        default_height = self.read_int(sprites, self.HEIGHT, None)

        for sprite in self.read_object(sprites, self.SPRITE, []):
            name = self.read_req_string(sprite, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            image = self.read_string(sprite, self.IMAGE, default_image)
            width = self.read_int(sprite, self.WIDTH, default_width)
            height = self.read_int(sprite, self.HEIGHT, default_height)
            x = self.read_req_int(sprite, self.X)
            y = self.read_req_int(sprite, self.Y)
            sprite_obj = style.Sprite(image, x, y, width, height)
            data.config.style.sprites[id] = sprite_obj