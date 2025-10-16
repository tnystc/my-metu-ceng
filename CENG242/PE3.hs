module PE3 where

data Cell = SpaceCraft Int | Sand | Rock Int | Pit deriving (Eq, Read, Show)

type Grid = [[Cell]]
type Coordinate = (Int, Int)

data Move = North | East | South | West | PickUp | PutDown deriving (Eq, Read, Show)

data Robot = Robot { name :: String,
                     location :: Coordinate,
                     capacity :: Int,
                     energy :: Int,
                     storage :: Int } deriving (Eq, Read, Show)

-------------------------------------------------------------------------------------------
--------------------------------- DO NOT CHANGE ABOVE -------------------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------
-------------------------------------- PART I ---------------------------------------------

isInGrid :: Grid -> Coordinate -> Bool
isInGrid grid (x,y) = y>=0 && y < length grid && x>=0 && x < length (grid !! y)

-------------------------------------------------------------------------------------------

totalCount :: Grid -> Int
totalCount grid = sum [count | row <- grid, cell <- row, Rock count <- [cell]]

-------------------------------------------------------------------------------------------

coordinatesOfPits :: Grid -> [Coordinate]
coordinatesOfPits grid = sort [(x,y) | (y,row) <- (zip[0..] grid), (x, cell) <- (zip[0..] row), Pit == cell]

-------------------------------------------------------------------------------------------

tracePath :: Grid -> Robot -> [Move] -> [Coordinate]
tracePath grid robot moves = moveRobot grid (location robot) (energy robot) moves False

------------------------------------- PART II ----------------------------------------------

energiseRobots :: Grid -> [Robot] -> [Robot]
energiseRobots grid robots =
    let spacecrafts = [(x, y) | (y, row) <- zip [0..] grid, (x, cell) <- zip [0..] row, isSpaceCraft cell]
    in map (energiseHelper spacecrafts) robots
-------------------------------------------------------------------------------------------

applyMoves :: Grid -> Robot -> [Move] -> (Grid, Robot)
applyMoves grid robot moves = apply grid robot moves False


---------------------- HELPERS -----------------------
sort :: [Coordinate] -> [Coordinate]
sort [] = []
sort (first:rest) = sortHelper first (sort rest)

sortHelper :: Coordinate -> [Coordinate] -> [Coordinate]
sortHelper first [] = [first]
sortHelper first (first2:rest)
    | first < first2 = first : first2 : rest
    | otherwise = first2 : sortHelper first rest
  
nextCoordinate :: Coordinate -> Move -> Coordinate
nextCoordinate (x, y) move =
    if move == North then (x, y - 1)
    else if move == East  then (x + 1, y)
    else if move == South then (x, y + 1)
    else if move == West  then (x - 1, y)
    else (x, y)
    
moveRobot :: Grid -> Coordinate -> Int -> [Move] -> Bool -> [Coordinate]
moveRobot _ coord _ [] _ = []
moveRobot grid coord energy (first:rest) yusufKuyuda
    | energy < cost =
        coord : moveRobot grid coord 0 rest yusufKuyuda
    | yusufKuyuda =
        coord : moveRobot grid coord (energy - cost) rest True
    |first `elem` [North, South, East, West] =
        let next = nextCoordinate coord first in
        if isInGrid grid next
            then if isPit grid next
                    then next : moveRobot grid next (energy - cost) rest True 
                 else next : moveRobot grid next (energy - cost) rest False 
        else coord : moveRobot grid coord (energy - cost) rest False     
    | otherwise =
        coord : moveRobot grid coord (energy - cost) rest yusufKuyuda
    where cost = energyCost first

                                
energyCost :: Move -> Int
energyCost North   = 1
energyCost South   = 1
energyCost East    = 1
energyCost West    = 1
energyCost PutDown = 3
energyCost PickUp  = 5

isPit :: Grid -> Coordinate -> Bool
isPit grid (x, y) = (grid !! y) !! x == Pit

isSpaceCraft :: Cell -> Bool
isSpaceCraft (SpaceCraft _) = True
isSpaceCraft _ = False

energiseHelper :: [Coordinate] -> Robot -> Robot
energiseHelper [] robot = robot
energiseHelper coord robot =
  let (rx, ry) = location robot
      distances = [abs (rx - sx) + abs (ry - sy) | (sx, sy) <- coord]
      fill = max 0 (100 - (minimum distances) * 20)
      newEnergy = min 100 (energy robot + fill)
  in robot { energy = newEnergy }


apply :: Grid -> Robot -> [Move] -> Bool -> (Grid, Robot)
apply grid robot [] _ = (grid, robot)
apply grid robot (first:rest) isStuck
    | energy robot < cost = apply grid (robot { energy = 0 }) rest isStuck
    | isStuck = apply grid (robot { energy = energy robot - cost }) rest True
    | first `elem` [North, South, East, West] =
        let next = nextCoordinate (location robot) first
        in if isInGrid grid next 
            then case (grid !! snd next) !! fst next of
                    Pit -> apply grid (robot { location = next, energy = energy robot - cost }) rest True
                    _ -> apply grid (robot { location = next, energy = energy robot - cost }) rest False
        else
            apply grid (robot { energy = energy robot - cost }) rest False
    | first == PickUp =
        let (x, y) = location robot 
            cell = (grid !! y) !! x
        in case cell of
            Rock count | count > 0 && storage robot < capacity robot ->
                let 
                    newCell = if count - 1 > 0 then Rock (count-1) else Sand
                    newGrid = updateGrid grid (x, y) newCell
                    newRobot = robot { storage = storage robot + 1, energy = energy robot - cost }
                in apply newGrid newRobot rest isStuck
            _ -> apply grid (robot { energy = energy robot - cost }) rest isStuck
    | first == PutDown =
        let (x, y) = location robot
            cell = (grid !! y) !! x
        in case cell of
            SpaceCraft count -> 
                let
                    newCell = SpaceCraft (count + 1)
                    newGrid = updateGrid grid (x, y) newCell
                    newRobot = robot { storage = storage robot - 1, energy = energy robot - cost }
                in apply newGrid newRobot rest isStuck
            _ -> apply grid (robot { energy = energy robot - cost }) rest isStuck
    | otherwise = apply grid (robot { energy = energy robot - cost }) rest isStuck
    where cost = energyCost first

updateGrid :: Grid -> Coordinate -> Cell -> Grid
updateGrid grid (x, y) newCell =
    take y grid ++ [take x (grid !! y) ++ [newCell] ++ drop (x + 1) (grid !! y)] ++ drop (y + 1) grid


