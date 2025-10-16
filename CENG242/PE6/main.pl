
% 5 POINTS
%
% get_count(ItemIDList,Type,ItemCount)
%
% find count of items of Type in a list of ItemIDs.
get_count([],_,0).
get_count([ItemID|ItemIDList],Type,ItemCount) :-
	get_count(ItemIDList,Type,Count),
	item(ItemID,Type,_,_,_,_),
	ItemCount is Count + 1,
	!.
get_count([ItemID|ItemIDList],Type,ItemCount) :-
	get_count(ItemIDList,Type,Count),
	item(ItemID,ItemType,_,_,_,_),
	ItemType \= Type,
	ItemCount is Count,
	!.



% 5 POINTS
%
% get_total_price(ItemIDList,TotalPrice)
%
% find the total price of items of Type in a list of ItemIDs.
get_total_price([],0).
get_total_price([ItemID|ItemIDList],TotalPrice) :-
	get_total_price(ItemIDList,Total),
	item(ItemID,_,_,_,Price,_),
	TotalPrice is Total + Price,
	!.



% 5 POINTS
%
% get_rating_of_look(ItemIDList,Rating)
%
% rating of a look is the average rating of the items in that look.
% get the average rating of items in a list of ItemIDs.
get_rating_of_look(ItemIDList,Rating) :-
	get_rating_total(ItemIDList,TotalRating),
	length(ItemIDList,ItemCount),
	ItemCount >= 1,
	Rating is TotalRating/ItemCount.
get_rating_of_look([],0).
% helper get_rating_total(ItemIDList,TotalRating)
get_rating_total([],0).
get_rating_total([ItemID|ItemIDList],TotalRating) :-
	get_rating_total(ItemIDList,Total),
	item(ItemID,_,_,_,_,Rating),
	TotalRating is Total + Rating,
	!.



% 10 POINTS
% get_items_for_requirement(Requirement,ItemIDList)
%
% get all items that fit a given requirement.
% each "Requirement" is a 3-tuple of the form (Type,Colour,Style).
% however, not all fields need to be specified. 
% following are all valid Requirements:
% - (Type,Colour,Style)
% - (_,Colour,Style)
% - (Type,_,Style)
% - (Type,Colour,_)
% - (_,_,Style)
% - (Type,_,_)
% - (_,Colour,_)
% - (_,_,_)
get_items_for_requirement((Type,Colour,Style),ItemIDList) :-
	findall(ItemID, item(ItemID,Type,Colour,Style,_,_), ItemIDList).



% 15 POINTS
% is_valid_look(ItemIDList)
%
% a valid look should have:
% either
%	a "singlepiece" item 
% or
% 	one "top" item and one "bottom" item
% and also
% - at most three "accessory" items (can be zero)
% - at most one "shoe" item (can be zero)
% - at most one "jacket" item (can be zero)
is_valid_look(ItemIDList) :-
	get_count(ItemIDList,singlepiece,SinglePieceCount),
	get_count(ItemIDList,top,TopCount),
	get_count(ItemIDList,bottom,BottomCount),
	get_count(ItemIDList,shoe,ShoeCount),
	get_count(ItemIDList,jacket,JacketCount),
	get_count(ItemIDList,accessory,AccessoryCount),
	SinglePieceCount is 0,
	TopCount is 1, BottomCount is 1,
	ShoeCount =< 1, JacketCount =< 1,
	AccessoryCount =< 3,
	!.
is_valid_look(ItemIDList) :-
	get_count(ItemIDList,singlepiece,SinglePieceCount),
	get_count(ItemIDList,top,TopCount),
	get_count(ItemIDList,bottom,BottomCount),
	get_count(ItemIDList,shoe,ShoeCount),
	get_count(ItemIDList,jacket,JacketCount),
	get_count(ItemIDList,accessory,AccessoryCount),
	SinglePieceCount is 1,
	TopCount is 0, BottomCount is 0,
	ShoeCount =< 1, JacketCount =< 1,
	AccessoryCount =< 3,
	!.



% 20 POINTS
% is_look_valid_for_competition(CompetitionID,ItemIDList)
%
% a look is valid for a competition if it is a valid look and there is
% at least one item in the look that fits the competition requirement.
is_look_valid_for_competition(CompetitionID,ItemIDList) :-
	is_valid_look(ItemIDList),
	is_look_valid_for_requirement(CompetitionID,ItemIDList).
% helper is_look_valid_for_requirement((Type,Colour,Style),ItemIDList)
is_look_valid_for_requirement(CompetitionID,[ItemID|_]) :-
	competition(CompetitionID,(Type,Colour,Style)),
	item(ItemID,Type,Colour,Style,_,_),
	!.
is_look_valid_for_requirement(CompetitionID,[ItemID|ItemIDList]) :-
	competition(CompetitionID,(Type,Colour,Style)),
	item(ItemID,_,_,_,_,_),
	is_look_valid_for_requirement(CompetitionID,ItemIDList).



% 20 POINTS
% generate_look(ItemIDList) 
%
% generate a new valid look from all items with each ";" press.
generate_look(SelectedItems) :-
	item(SinglePiece,singlepiece,_,_,_,_),
	get_shoe_or_none(Shoe),
	get_jacket_or_none(Jacket),
	get_items_for_requirement((accessory,_,_),AllAccessories),
	subsequence(SelectedAccessories,AllAccessories),
	append([SinglePiece],Jacket,Med1),
	append(SelectedAccessories,Shoe,Med2),
	append(Med1,Med2,SelectedItems),
	is_valid_look(SelectedItems).
generate_look(SelectedItems) :-
	item(Top,top,_,_,_,_),
	item(Bottom,bottom,_,_,_,_),
	get_shoe_or_none(Shoe),
	get_jacket_or_none(Jacket),
	get_items_for_requirement((accessory,_,_),AllAccessories),
	subsequence(SelectedAccessories,AllAccessories),
	append([Top,Bottom],Shoe,Med1),
	append(SelectedAccessories,Jacket,Med2),
	append(Med1,Med2,SelectedItems),
	is_valid_look(SelectedItems).
get_shoe_or_none([Shoe]) :- item(Shoe,shoe,_,_,_,_).
get_shoe_or_none([]).
get_jacket_or_none([Jacket]) :- item(Jacket,jacket,_,_,_,_).
get_jacket_or_none([]).
subsequence([], _).   
subsequence([X|T1], [X|T2]) :- subsequence(T1, T2).
subsequence([X|T1], [_|T2]) :- subsequence([X|T1], T2).
	

% 10 POINTS
% generate_look_for_competition(UserID,CompetitionID,ItemIDList)
% 
% for a user to enter a competition:
% - they must be able to afford a look
% - the look must fit the competition requirements
% generate a new look with each ";" press.
%
% hint: you can combine "is_look_valid_for_competition" and "generate_look"
% other solutions are also accepted.
generate_look_for_competition(UserID,CompetitionID,ItemIDList) :-
	generate_look(ItemIDList),
	is_look_valid_for_competition(CompetitionID,ItemIDList),
	user(UserID,Money),
	get_total_price(ItemIDList,TotalPrice),
	TotalPrice =< Money.
generate_look_for_competition(_,_,[]).



% 10 POINTS
% get_highest_rated_look(ListOfLooks,BestLook)
%
% given a list of looks, find the look with the highest rating.
get_highest_rated_look([],[]).
get_highest_rated_look([Look|ListOfLooks],BestYet) :-
	get_rating_of_look(Look,CurrRating),
	get_highest_rated_look(ListOfLooks,BestYet),
	get_rating_of_look(BestYet,BestRating),
	CurrRating < BestRating.
get_highest_rated_look([Look|ListOfLooks],Look) :-
	get_rating_of_look(Look,CurrRating),
	get_highest_rated_look(ListOfLooks,BestYet),
	get_rating_of_look(BestYet,BestRating),
	CurrRating >= BestRating.