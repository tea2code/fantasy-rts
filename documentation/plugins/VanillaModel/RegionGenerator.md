# Region Generator

The blocks of a region are created by a region generator. At the beginning a region may be completly empty but at the same moment a block is requested for the first time it will be created by the generator.

## Map Parser

Static maps can be generated using map parsers. 

### BMB Map Parser

Generates static maps of certain z-levels based on a bitmap and a mapping between pixel color and a list of entities.

Teleport for slopes is supported by using the optional values `teleport_up` and/or `teleport_down`. If set the parser tries to find the another corresponding block and connects both.

#### Configuration

    bmpmap:

        namespace: <string>
    
        height: <integer greater 0>
        width: <integer greater 0>
        
        levels:
            - level: <integer>
              image: <string representing an id>
        
        images:
            namespace: <string>
            
            images:
                - name: <string>
                  path: <string>
        
        colors:
            neutral:
                r: <integer between 0 and 255>
                g: <integer between 0 and 255>
                b: <integer between 0 and 255>
        
            colors:
                - r: <integer between 0 and 255>
                  g: <integer between 0 and 255>
                  b: <integer between 0 and 255>
                  teleport_up: <boolean, optional>
                  teleport_down: <boolean, optional>
                  entities:  
                    - <string representing an id>

### Text Map Parser

TODO

## Dynamic Region Generation

TODO