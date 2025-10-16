module PE1 where

data Author = Author String Int deriving (Eq, Show)
data Book = Book String Author Int Int deriving (Eq, Show)
data Library = Library [(Book, Int, Int)] deriving (Eq, Show)

---------- Do not change anything above this line ----------

publicationAge :: Book -> Int
publicationAge (Book _  (Author _ birth) publish _) = publish - birth

booksByAuthor :: Author -> Library -> [Book]
booksByAuthor author1 (Library lib) = [ res | (res@(Book _ author2 _ _), _, _) <- lib, author1 == author2]

shortBooks :: Library -> [Book]
shortBooks (Library lib) = [ res | (res@(Book _ _ _ n), _, _) <- lib, n <= 200]

bookInCollection :: String -> Library -> Bool
bookInCollection name lib = name `elem` map getName (getBooks lib)

totalPagesByAuthor :: Author -> Library -> Int
totalPagesByAuthor auth lib = sum [pages | Book _ _ _ pages<-(booksByAuthor auth lib)]

averageBookLength :: Library -> Int
averageBookLength lib = sum [pages | Book _ _ _ pages<-(getBooks lib)] `div` (length (getBooks lib))

authorsWithLongBooks :: Int -> Library -> [Author]
authorsWithLongBooks minPage (Library lib) = 
        removeDup [auth | (Book _ auth _ _ ) <- [ book | (book@(Book _ _ _ n), _, _) <- lib, n >= minPage]]
    where
        removeDup [] = []
        removeDup (hd:remain)
            | hd `elem` remain = removeDup remain
            | otherwise = hd:removeDup remain

findYoungestAuthor :: Library -> Author
findYoungestAuthor (Library lib) = let books = [book | (book, _, _) <- lib]
                                   in getAuth (minAge books)

newArrivals :: Library -> [(Int, Book)] -> Library
newArrivals (Library lib) newBooks = Library (foldl (\newLib newBook -> arrivalHelper newBook newLib) lib newBooks)

-- This is a helper function that gives you a list of just the books in a library,
-- with the [Book] type, without the library availability information.
-- It might come in handy for many questions.
-- You may change and improve it to better fit you solution, if you want to.
getBooks :: Library -> [Book]
getBooks (Library books) = map (\(x,_,_) -> x) books
getName:: Book -> [Char]
getName (Book name _ _ _) = name
getAuth:: Book -> Author
getAuth (Book _ auth _ _) = auth
minAge:: [Book] -> Book
minAge [book] = book
minAge (book1:book2:remain) = if publicationAge book1 < publicationAge book2 then minAge (book1:remain)
                              else minAge(book2:remain)
arrivalHelper:: (Int, Book) -> [(Book, Int, Int)] -> [(Book, Int, Int)]
arrivalHelper (n, book) [] = [(book,n,n)]
arrivalHelper (n, book) ((oldBook, total, available):remain) = if book == oldBook then (book, total+n, available+n):remain
                                                               else (oldBook, total, available):arrivalHelper (n, book) remain
