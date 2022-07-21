#include "testSuite.h"
#define BOOST_TEST_MODULE MyTest TestSuites
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(suite1)

BOOST_AUTO_TEST_CASE(inventoryTest) {

    //creates inventory - Will automatically have primary as pistol and secondary as none
    Inventory *i = new Inventory(QRectF(0,0,10,10));

    BOOST_CHECK(i->getGunPrim()->getGunType() == "Pistol");
    BOOST_CHECK(i->getGunSec()->getGunType() == "None");

    i->setGunPrim(Gun("Assault Rifle", QRectF(0,0,10,10)));
    BOOST_CHECK(i->getGunPrim()->getGunType() == "Assault Rifle");
    BOOST_CHECK(i->getGunSec()->getGunType() == "None");

    i->setGunSec(Gun("Assault Rifle", QRectF(0,0,10,10)));
    BOOST_CHECK(i->getGunPrim()->getGunType() == "Assault Rifle");
    BOOST_CHECK(i->getGunSec()->getGunType() == "Assault Rifle");

    i->setGunSec(Gun("Pistol", QRectF(0,0,10,10)));
    BOOST_CHECK(i->getGunPrim()->getGunType() == "Assault Rifle");
    BOOST_CHECK(i->getGunSec()->getGunType() == "Pistol");

    delete i;
}
    
BOOST_AUTO_TEST_CASE(BulletCollision) {
    QGraphicsRectItem rect(10, 10, 100, 100);
    Bullet bullets(10, 10, 1, 1, "Pistol", 10); 
    bullets.moveBullet();
    BOOST_CHECK_EQUAL(bullets.collidesWithItem(&rect), 1);
}

BOOST_AUTO_TEST_CASE(PlayerCollisionWithBullet) {
    QGraphicsRectItem *rect = new QGraphicsRectItem(10, 10, 100, 100);
    Player *bullets = new Player(10, 10, 1); 
    BOOST_CHECK_EQUAL(bullets->collidesWithItem(rect), 1);

    //Player position is at x = 30, y = 30
    Player *p = new Player(30, 30, 0);
    BOOST_CHECK_EQUAL(p->pos().x(), 30);
    BOOST_CHECK_EQUAL(p->pos().y(), 30);

    //Move player 10 units to right and 10 units down
    p->setPos(p->pos().x() + 10 , p->pos().y() + 10);
    BOOST_CHECK_EQUAL(p->pos().x(), 40);
    BOOST_CHECK_EQUAL(p->pos().y(), 40);

    //Turn the player 90 degrees to the right
    p->setRotation(p->rotation() + 90);
    BOOST_CHECK_EQUAL(p->rotation(), 90);

    delete rect;
    delete bullets;
    delete p;

}

BOOST_AUTO_TEST_CASE(PlayerCollidesWithPlayer) {
    Player *p1 = new Player(0,0,0);
    Player *p2 = new Player(0,0,0);
    BOOST_REQUIRE(p1);
    BOOST_REQUIRE(p2);
    BOOST_CHECK(p1->collidesWithItem(p2));
    delete p1;
    delete p2;
}

BOOST_AUTO_TEST_CASE(menuButtonTestCollision) {
    // QApplication is needed for modules that contain QGraphicsText...
    QApplication a(boost::unit_test::framework::master_test_suite().argc, boost::unit_test::framework::master_test_suite().argv);
    QString testWord("Test");
    MenuButton *menuButton = new MenuButton(0,0,100,100, testWord);
    BOOST_REQUIRE(menuButton);
    BOOST_CHECK(menuButton->pointCollision(50,50));
    BOOST_CHECK(!menuButton->pointCollision(-1,50));
    BOOST_CHECK(!menuButton->pointCollision(50,-1));
    BOOST_CHECK(!menuButton->pointCollision(101,50));
    BOOST_CHECK(!menuButton->pointCollision(50,101));
    delete menuButton;
}


BOOST_AUTO_TEST_CASE(damageTest) {
    Player * p = new Player(200, 200, 0);
    Enemy * e = new Enemy("Grunt", 100, 100, 0, 100, 3, 5, 30);
    e->hit(20);
    BOOST_CHECK_EQUAL(e->getHealth(), 80);
    delete p;
    delete e;
}

BOOST_AUTO_TEST_CASE(killTest) {
    Player * p = new Player(200, 200, 0);
    Enemy * e = new Enemy("Grunt", 100, 100, 0, 100, 3, 5, 30);
    e->hit(100);
    BOOST_CHECK_LE(e->getHealth(), 0);
    delete p;
    delete e;
    
}



BOOST_AUTO_TEST_SUITE_END()
