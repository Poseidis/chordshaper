import { useState } from 'react'
import './App.css'

import { Text } from '@mantine/core'

const App = () => {
  const [count, setCount] = useState(0)

  return (
    <div>
      <Text>Welcome to Mantine!</Text>
    </div>
  )
};

export default App
