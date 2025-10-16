module PE2 where

data GridTree a = EmptyTree | GridTree a [GridTree a] deriving (Show, Eq)

findNode :: a -> GridTree a -> (Int, Int) -> a
findNode defaultParam tree coordinate =
  case lookup coordinate (setCoordinate tree) of
    Just value -> value
    Nothing  -> defaultParam

setCoordinate :: GridTree a -> [((Int, Int), a)]
setCoordinate EmptyTree = []
setCoordinate trees = getCoAndValue 0 [trees]
  where
    getCoAndValue :: Int -> [GridTree a] -> [((Int, Int), a)]
    getCoAndValue _ [] = []
    getCoAndValue lvl treeList =
      let 
          nonEmptyNodes = [ n | n@(GridTree _ _) <- treeList ]
          currentLevel = [ ((lvl, col), value) | (GridTree value _, col) <- zip nonEmptyNodes [0..] ]
          nextNodes    = concat [ children | GridTree _ children <- nonEmptyNodes ]
      in currentLevel ++ getCoAndValue (lvl + 1) nextNodes
      
      
findLocationOf :: Eq a => a -> GridTree a -> (Int, Int)
findLocationOf target tree = searchLevel 0 [(tree, 0)]
  where
    searchLevel _ [] = (-1, -1)
    searchLevel lvl nodes =
      let coords   = setCoordinates lvl nodes
          foundPos = lookup target (map toLookupPair coords)
      in case foundPos of
           Just pos -> pos
           Nothing  -> searchLevel (lvl + 1) (reassignColumns (concatMap getChildren nodes))
           
    setCoordinates :: Int -> [(GridTree a, Int)] -> [((Int, Int), a)]
    setCoordinates lvl nodes = [ ((lvl, col), value) | (GridTree value _, col) <- nodes ]
    
    getChildren :: (GridTree a, Int) -> [GridTree a]
    getChildren (GridTree _ children, _) = children
    getChildren (EmptyTree, _)     = []
    
    reassignColumns :: [GridTree a] -> [(GridTree a, Int)]
    reassignColumns xs = zip xs [0..]
    
    toLookupPair :: ((Int, Int), a) -> (a, (Int, Int))
    toLookupPair ((r, c), v) = (v, (r, c))




insertNode :: a -> GridTree a -> (Int, Int) -> GridTree a
insertNode _ x _ = x
