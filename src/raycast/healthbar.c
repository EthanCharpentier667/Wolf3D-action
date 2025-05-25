/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** healhbar
*/

#include "frame.h"

static sfColor get_health_color(float health_percent)
{
    if (health_percent < 0.3f)
        return sfRed;
    else if (health_percent < 0.6f)
        return sfYellow;
    else
        return sfGreen;
}

static sfRectangleShape* create_health_bar_background(void)
{
    sfRectangleShape *bg = sfRectangleShape_create();

    if (!bg)
        return NULL;
    sfRectangleShape_setPosition(bg, v2f(0, 0));
    sfRectangleShape_setSize(bg, v2f(100, 10));
    sfRectangleShape_setFillColor(bg, sfColor_fromRGB(80, 80, 80));
    sfRectangleShape_setOutlineThickness(bg, 1.0f);
    sfRectangleShape_setOutlineColor(bg, sfBlack);
    return bg;
}

static sfRectangleShape* create_health_bar_fill(frame_t *frame, int index)
{
    float health_percent = (float)ENEMY[index].life
        / (float)ENEMY[index].max_life;
    sfRectangleShape *fill = sfRectangleShape_create();

    sfRectangleShape_setPosition(fill, v2f(0, 0));
    sfRectangleShape_setSize(fill, v2f(100 * health_percent, 10));
    sfRectangleShape_setFillColor(fill, get_health_color(health_percent));
    return fill;
}

static sfRenderTexture* create_health_bar_texture(frame_t *frame, int index)
{
    sfRenderTexture *render_tex = sfRenderTexture_create(100, 10, sfFalse);
    sfRectangleShape *bg = create_health_bar_background();
    sfRectangleShape *fill = create_health_bar_fill(frame, index);

    if (!render_tex || !bg || !fill) {
        if (render_tex)
            sfRenderTexture_destroy(render_tex);
        if (bg)
            sfRectangleShape_destroy(bg);
        if (fill)
            sfRectangleShape_destroy(fill);
        return NULL;
    }
    sfRenderTexture_clear(render_tex, sfTransparent);
    sfRenderTexture_drawRectangleShape(render_tex, bg, NULL);
    sfRenderTexture_drawRectangleShape(render_tex, fill, NULL);
    sfRenderTexture_display(render_tex);
    sfRectangleShape_destroy(bg);
    sfRectangleShape_destroy(fill);
    return render_tex;
}

static void calculate_health_bar_position(frame_t *frame,
    sfVector2f enemy_infos, const sfTexture *health_texture,
    item_render_data_t *health_data)
{
    sfVector3f healthbar_pos = {
        ENEMY[(int) enemy_infos.x].pos.x,
        ENEMY[(int) enemy_infos.x].pos.y,
        ENEMY[(int) enemy_infos.x].pos.z + enemy_infos.y
    };

    calculate_item_position(frame, healthbar_pos,
        (sfTexture *)health_texture, health_data);
    calculate_item_dimensions(health_data, v2f(0.5f, 0.15f),
        PLAYER, healthbar_pos);
}

void draw_health_bar_3d(frame_t *frame, int index,
    float enemyheight, sfVector2f bar_scale)
{
    sfRenderTexture *render_tex = create_health_bar_texture(frame, index);
    const sfTexture *health_texture = sfRenderTexture_getTexture(render_tex);
    item_render_data_t health_data = {0};

    if (!render_tex || !health_texture)
        return;
    enemyheight = 1.0f;
    if (ENEMY[index].type == HITLER2 || ENEMY[index].type == HITLER)
        enemyheight = 1.2f;
    if (ENEMY[index].type == BASICBLUE)
        enemyheight = 1.2f;
    calculate_health_bar_position(frame, v2f(index, enemyheight),
        health_texture, &health_data);
    render_item_columns(frame, (sfTexture *)health_texture,
        &health_data, bar_scale);
    sfRenderTexture_destroy(render_tex);
}
