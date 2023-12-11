#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"
#include "../../src/shared/state/GameState.h"

using namespace ::state;


BOOST_AUTO_TEST_CASE(TestState){

    Card card{"card1", CardType::Military, 2};
    BOOST_CHECK_EQUAL(card.getNameOfCard(), std::string("card1"));
    BOOST_CHECK_EQUAL(card.getColorOfCard(), CardType::Military);
    BOOST_CHECK_EQUAL(card.getCostOfCard(), 2);

    Card cardReligious{"card2", CardType::Religious, 4};
    BOOST_CHECK_EQUAL(cardReligious.getNameOfCard(), std::string("card2"));
    BOOST_CHECK_EQUAL(cardReligious.getColorOfCard(), CardType::Religious);
    BOOST_CHECK_EQUAL(cardReligious.getCostOfCard(), 4);

    Card cardCommercial{"card3", CardType::Commercial, 8};
    BOOST_CHECK_EQUAL(cardCommercial.getNameOfCard(), std::string("card3"));
    BOOST_CHECK_EQUAL(cardCommercial.getColorOfCard(), CardType::Commercial);
    BOOST_CHECK_EQUAL(cardCommercial.getCostOfCard(), 8);

    Card cardNoble{"card1", CardType::Noble, 2};
    BOOST_CHECK_EQUAL(cardNoble.getColorOfCard(), CardType::Noble);

    Card cardWonder{"card1", CardType::Wonder, 2};
    BOOST_CHECK_EQUAL(cardWonder.getColorOfCard(), CardType::Wonder);

    std::string playerName = "player1";
    Player plr{playerName, PlayerId::PlayerA};
    BOOST_CHECK_EQUAL(plr.getNameOfPlayer(), "player1");
    BOOST_CHECK_EQUAL(plr.getIdOfPlayer(), PlayerId::PlayerA);
    BOOST_CHECK_EQUAL(plr.getCharacter(), CharacterType::NoCharacter);
    std::vector<Card> hand{card};
    plr.setHand(hand);
    BOOST_CHECK_EQUAL(plr.getHand()[0].getNameOfCard(), hand[0].getNameOfCard());
    BOOST_CHECK_EQUAL(plr.getNumberOfCards(), 1);
    plr.setNumberOfCoins(5);
    BOOST_CHECK_EQUAL(plr.getNumberOfCoins(), 5);
    std::vector<Card> board;
    plr.setBoardOfPlayer(board);
    BOOST_CHECK_EQUAL(plr.getBoardOfPlayer().size(), board.size());
    plr.setCharacter(CharacterType::Warlord);
    BOOST_CHECK_EQUAL(plr.getCharacter(), CharacterType::Warlord);

    GameState gameState{std::vector<Player>{plr}};
    BOOST_CHECK_EQUAL(gameState.getListOfPlayer().size(), 1);
    BOOST_CHECK_EQUAL(gameState.getCurrentCharacter(), CharacterType::NoCharacter);
    BOOST_CHECK_EQUAL(gameState.getGamePhase(), Phase::CHOOSECHARACTER);

    gameState.setCrownOwner(PlayerId::PlayerA);
    BOOST_CHECK_EQUAL((gameState.getCrownOwner()), plr.getIdOfPlayer());

    gameState.setCurrentCharacter(CharacterType::King);
    BOOST_CHECK_EQUAL(gameState.getCurrentCharacter(), CharacterType::King);

    gameState.setPlaying(PlayerD);
    BOOST_CHECK_EQUAL(gameState.getPlaying(), PlayerD);

    BOOST_CHECK_EQUAL(gameState.getPlayer(PlayerA).getNameOfPlayer(), plr.getNameOfPlayer());
    BOOST_CHECK_THROW(gameState.getPlayer(PlayerD), std::exception);
    BOOST_CHECK_NO_THROW(gameState.updatePlayer(plr));

    plr.setCapacityAvailability(true);
    gameState.updatePlayer(plr);

    BOOST_CHECK_EQUAL(gameState.getPlayer(PlayerA).getCapacityAvailability(),true);

}

/* vim: set sw=2 sts=2 et : */
