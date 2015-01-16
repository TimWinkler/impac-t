// Copyright (c) 2015 Oliver Lau <oliver@ersatzworld.net>
// All rights reserved.

#include "stdafx.h"

namespace Breakout {


  Block::Block(int index, Game *game)
    : Body(Body::BodyType::Block, game)
  {
    setZIndex(Body::ZIndex::Foreground + 0);
    mTexture = TextureCache::texture(index);
    mName = "Block";

    const float W = float(mTexture.getSize().x);
    const float H = float(mTexture.getSize().y);

    mSprite.setTexture(mTexture);
    mSprite.setOrigin(0.5f * W, 0.5f * H);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.angle = 0.f;
    bd.linearDamping = 9.5f;
    bd.angularDamping = 0.21f;
    bd.gravityScale = .001f;
    bd.allowSleep = true;
    bd.awake = false;
    bd.fixedRotation = false;
    bd.bullet = false;
    bd.active = true;
    bd.userData = this;
    mBody = game->world()->CreateBody(&bd);

    const float sx = 1.f / game->tileWidth();
    const float sy = 1.f / game->tileHeight();

    b2PolygonShape polygon;
    polygon.SetAsBox(0.5f * (W - 8) * sx, 0.5f * H * sy);

    b2FixtureDef fdBox;
    fdBox.shape = &polygon;
    fdBox.density = 11.f;
    fdBox.friction = .7f;
    fdBox.restitution = 0.9f;
    mBody->CreateFixture(&fdBox);

    b2CircleShape circleL;
    circleL.m_p.Set(-8.f * sx, 0.f);
    circleL.m_radius = 8.f * sx;

    b2FixtureDef fdCircleL;
    fdCircleL.shape = &circleL;
    fdCircleL.density = 11.f;
    fdCircleL.friction = .7f;
    fdCircleL.restitution = 0.95f;
    mBody->CreateFixture(&fdCircleL);

    b2CircleShape circleR;
    circleR.m_p.Set(+8.f * sx, 0.f);
    circleR.m_radius = 8.f * sx;

    b2FixtureDef fdCircleR;
    fdCircleR.shape = &circleR;
    fdCircleR.density = 11.f;
    fdCircleR.friction = .7f;
    fdCircleR.restitution = 0.95f;
    mBody->CreateFixture(&fdCircleR);
  }


  void Block::onUpdate(float elapsedSeconds)
  {
    UNUSED(elapsedSeconds);
    mSprite.setPosition(mGame->tileWidth() * mBody->GetPosition().x, mGame->tileHeight() * mBody->GetPosition().y);
    mSprite.setRotation(mBody->GetAngle() * _RAD2DEG);
  }


  void Block::onDraw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    target.draw(mSprite, states);
  }

}