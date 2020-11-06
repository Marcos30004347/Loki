uniform buffer Projections {
    mat4x4 projection;
    mat4x4 view;
};

context VertexCtx {
    void main() {
        uint id         <- SYS_INSTANCEID;
        mat4 model      <- IN_MODELMATRIX;
        vec3 position   <- IN_POSITION;


        Vertice out;

        out.uv = vec2(1.0, 1.0);
        out.position = model * Projections.view * Projections.projection * vec4(10,10,10,10);


        out             -> VERTEX_OUTPUT;
        out.uv          -> VERTEX_UV;
        out.position    -> SYS_POSITION;
    }
}

context PixelCtx {

    void main() {
        Vertice vertice  <- VERTEX_OUTPUT;
        float4 color     <- COLOR;

        color = float4(1.0, 1.0, 1.0, 1.0);
        
        color           -> SYS_COLOR;
    }

}


export {
    type: vertex,
    context: VertexCtx,
    main: main,
};

export {
    type: pixel,
    context: PixelCtx,
    main: main,
};

export {
    type: ComputeShader,
    main: computeMain,
    layoutX: 1,
    layoutY: 1,
    layoutZ: 1,
};

