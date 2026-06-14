CXX= g++ -g -std=c++20
FILES = sources/main.o sources/admin.o sources/CasualMatch.o sources/commandhandler.o sources/exceptions.o sources/game.o sources/invitation.o sources/matchplayer.o sources/player.o sources/report.o sources/user.o sources/match.o sources/rankedmatch.o
EXE= UTGame

all : $(EXE)


$(EXE) : $(FILES)
	$(CXX) $^ -o $@
game.o : sources/game.cpp sources/game.hpp sources/user.hpp sources/player.hpp sources/admin.hpp sources/CasualMatch.hpp sources/invitation.hpp sources/report.hpp sources/exceptions.hpp sources/constants.hpp sources/match.hpp sources/rankedmatch.hpp
	$(CXX) -c $< -o $@
admin.o : sources/admin.cpp sources/admin.hpp sources/user.hpp sources/constants.hpp
	$(CXX) -c $< -o $@
user.o : sources/user.cpp sources/user.hpp sources/invitation.hpp sources/exceptions.hpp
	$(CXX) -c $< -o $@
CasualMatch.o : sources/CasualMatch.cpp sources/CasualMatch.hpp sources/constants.hpp
	$(CXX) -c $< -o $@
matchplayer.o : sources/matchplayer.cpp sources/matchplayer.hpp sources/user.hpp sources/constants.hpp
	$(CXX) -c $< -o $@
commandhandler.o : sources/commandhandler.cpp sources/commandhandler.hpp sources/game.hpp
	$(CXX) -c $< -o $@
exceptions.o : sources/exceptions.cpp sources/exceptions.hpp
	$(CXX) -c $< -o $@
invitation.o : sources/invitation.cpp sources/invitation.hpp sources/user.hpp
	$(CXX) -c $< -o $@
player.o : sources/player.cpp sources/player.hpp sources/invitation.hpp sources/user.hpp sources/constants.hpp
	$(CXX) -c $< -o $@
report.o : sources/report.cpp sources/report.hpp
	$(CXX) -c $< -o $@h
match.o : sources/match.cpp sources/match.hpp sources/matchplayer.hpp sources/exceptions.hpp
	$(CXX) -c $< -o $@
rankedmatch.o : sources/rankedmatch.cpp sources/rankedmatch.hpp sources/match.hpp sources/constants.hpp
	$(CXX) -c $< -o $@
main.o : sources/main.cpp sources/game.hpp sources/commandhandler.hpp
	$(CXX) -c $< -o $@
.PHONY : all clean
clean:
	rm -f $(FILES) $(EXE)
