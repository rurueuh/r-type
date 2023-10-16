# RType
![Language](https://img.shields.io/badge/Language-C++-0052cf)

### A compiler for asm

This project is part of the 3rd year at Epitech
The goal of this project is to create a multiplayer version of the [R-Type game](https://fr.wikipedia.org/wiki/R-Type).
Aside from that, we need to create our own Game Engine.

To accomplish the project, we need to developp an ECS (Entity Component System), wich is an architectural pattern often used in game development.

<p align="center">
	<img src="./Assets/presentation.png">
</p>

# Summary

* **[Summary](#summary)**
# Summary

**[Features](#features)**
   * **[World](#world)**
   * **[Entity Component System](#entity-component-system)**
      * **[Entity](#entity)**
      * **[Component](#component)**
      * **[System](#system)**
**[Network](#network)**
   * **[Server side](#server-side)**
      * **[Communication Protocol](#communication-protocol)**
      * **[Data Processing](#data-processing)**
      * **[Error Handling](#error-handling)**
   * **[Client side](#client-side)**
      * **[Connecting to the Server](#connecting-to-the-server)**
      * **[Synchronization with the Server](#synchronization-with-the-server)**
      * **[Handling Disconnections](#handling-disconnections)**
      * **[User Interface](#user-interface)**
      * **[User Interaction](#user-interaction)**
**[Compilation](#compilation)**
   * **[Linux](#linux)**
   * **[Windows](#windows)**
**[Run](#run)**
   * **[Windows](#windows-1)**
   * **[Linux](#linux-1)**
**[Credits](#credits)**


# Features

## World

Our game engine is designed around a world, wich is the instance where the game is playing. It is where the entities are stored and the systems runs.

## Entity Component System

An ECS is a way to architecture the code that allow you to create **entities**, and then bind to them various **components** wich will define attributes to the entities. After that, you can create **systems** to define what need to be done for each of the components that exist in the game engine.

### Entity
 An entity is a fundamental object in an ECS. It is essentially a container for components. Entities are created dynamically and can represent various elements in a game, such as players, enemies, items, etc. In your code example, an entity named player is created using `_world->CreateEntity();`.

### Component
A component is a piece of data that holds attributes or properties of an entity. For example, a PositionComponent may hold x and y coordinates of an entity. Components are used to define the various aspects or characteristics of entities.

For instance, in a simple game, you might have a PositionComponent to determine the position of an entity and a DrawableComponent to determine how it should be rendered.

### System

A system is a part of the ECS that defines behavior or functionality in the game. It operates on entities based on the components they possess. Systems are responsible for processing specific sets of components and updating the game state accordingly.

Systems encapsulate specific logic, such as rendering, physics, input handling, etc. They iterate through entities with specific components and perform operations on them.

For example, you might have a RenderingSystem that updates the visual representation of entities, or a MovementSystem that updates the position of entities.

# Network

In our system, we employ a server-centric architecture, where the server is responsible for sending and receiving data from each client. If a client is no longer connected to the server, the client adapts to an "improvised" mode for displaying data.

## Server side

The server side of our architecture plays a crucial role in managing the flow of data between clients. It maintains a constant connection with each client, ensuring that information is transmitted efficiently and reliably.

### Communication Protocol

The server utilizes a specific communication protocol to facilitate seamless interaction. This protocol defines the rules and conventions for data exchange, ensuring that both the server and clients understand each other's messages.

### Data Processing

Upon receiving data from a client, the server processes it according to the established logic. This may involve tasks such as updating game state, handling player actions, and broadcasting relevant information to all connected clients.

### Error Handling

To maintain stability and reliability, the server incorporates robust error-handling mechanisms. It can detect when a client disconnects unexpectedly and take appropriate action to manage the situation.

## Client side

Clients in our system primarily focus on providing a user-friendly interface and rendering game elements based on the information received from the server.

### Connecting to the Server

Upon starting, a client establishes a connection with the server. This connection remains active throughout the client's session, allowing for continuous data exchange.

### Synchronization with the Server

Clients regularly synchronize with the server to ensure they have the most up-to-date information. This involves sending periodic updates about the client's state and receiving relevant data from the server.

### Handling Disconnections

In the event that a client loses its connection to the server, it enters an "improvised" mode. During this state, the client may rely on cached data or user input to simulate certain aspects of the game. However, it's important to note that the client's functionality may be limited compared to when it is fully connected.

### User Interface

The client's user interface (UI) is responsible for presenting information to the player. It interprets the data received from the server and renders it in a visually appealing and intuitive manner.

### User Interaction

Clients also manage user input, allowing players to interact with the game. This includes actions like moving characters, performing actions, and making decisions within the game environment.

---

This network architecture ensures a smooth and responsive multiplayer experience, even in scenarios where a client's connection status may fluctuate. It emphasizes reliable communication between the server and clients, ultimately contributing to an engaging and enjoyable gameplay experience.



# compilation
dans le terminal du dossier:
   `git submodule update --init --recursive`
`cmake`
`build`

# Linux
There is the file .sh that allow you to build and install the complete game :

# Windows
There is the file .bat that allow you to build and install the complete game :

# Run
## Windows
Execute rtype-client.exe || rtype-server.exe

## Linux
`./Build-linux/client`
`Build-linux/server`


# Credits
* [**Alan**](https://github.com/tsuzuedev) : Contributor
* [**Maximilien**](https://github.com/rurueuh) : Contributor
* [**Ulysse**](https://github.com/Odyce) : Contributor 