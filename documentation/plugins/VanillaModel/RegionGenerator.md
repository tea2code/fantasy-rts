# Region Generator

The blocks of a region are created by a region generator. At the beginning a region may be completely empty but at the same moment a block is requested for the first time it will be created by the generator.

## Map Parser

Static maps can be generated using map parsers. 

### BMB Map Parser

Generates static maps of certain z-levels based on a bitmap and a mapping between pixel color and a list of entities.

Teleport for slopes is supported by using the optional values `teleport_up` and/or `teleport_down`. If set the parser tries to find the another corresponding block and connects both.

General teleport is also supported using the optional `teleport`. A color with the same teleport ID should only exists twice. Both points will represent a portal to the other point.

#### Configuration

    bmp_map:

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
                  teleport: <string representing an id, optional>
                  entities:  
                    - <string representing an id>

### Text Map Parser

TODO

#### Configuration

TODO

    text_map:

## Dynamic Region Generation

The current region generator uses a combination of default entities for the surface, below and above, a static map parser for surface structures and a noise based dynamic generation of structures below the surface. It has no intention to be realistic in any way and is more of a prove of concept.

#### Configuration

    region_generator:
        
        default_above: <string representing an id>
        default_surface: <string representing an id>
        default_below: <string representing an id>
    
        noise_map:
    
            namespace: <string>
            
            levels:
            
                default_below:
                    - <string representing an id>
            
                levels:
                    - level: <integer>
                      generators: 
                        - <string representing an id>
                        
            generators:
                namespace: generator
                
                generators:
                    - name: <string>
                      feature_size: <float bigger 0>
                      ranges:
                        - start: <float between -1 and 1>
                          end: <float between -1 and 1>
                      entities:
                        - <string representing an id>