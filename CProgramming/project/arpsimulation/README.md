# ROUTING TABLE & ARP table manitenence with client server
---

## 🎯 Project Objectives

* Build a **client–server system in C** that replicates core ideas of routing and ARP tables.
* Learn and apply **UNIX IPC mechanisms**: Unix domain sockets, shared memory, message queues, and signals.
* Ensure **synchronization** between multiple clients and a single server.
* Provide an **admin control interface** for server to manage tables and clients.
* Extend to **TCP sockets** to run across machines.

---

## 🪜 Project Stages

### Stage 1 – Minimal Client–Server with Unix Domain Sockets

**Objective:** Get a server and a client talking via Unix domain sockets.

* **Tasks:**

  * Server listens on a Unix domain socket path.
  * Client connects and sends a “HELLO” message.
  * Server responds with “WELCOME.”
* **Outcome:** You can run server, connect with multiple clients, see message exchange.
* **How to Test:** Run server, start 2 clients, see each gets a welcome reply.

---

### Stage 2 – Routing Table Replication

**Objective:** Implement a routing table in the server and synchronize with clients.

* **Tasks:**

  * Define `struct route { char src[16]; char mask[16]; char dst[16]; char iface[16]; }`.
  * Server keeps a list of routes in memory.
  * On client connect, server sends full table dump.
  * On update (add/remove/modify), server pushes delta to all clients.
  * Client stores local copy of routing table.
* **Outcome:** Clients always have the same table as server.
* **How to Test:** Update route in server menu, check that all clients print/log updated table.

---

### Stage 3 – ARP Table with Shared Memory + Message Queue

**Objective:** Use shared memory for IP–MAC mapping, message queue for synchronization.

* **Tasks:**

  * Server maintains MAC list in process memory.
  * Server maintains IP–MAC mapping in shared memory.
  * When server adds a MAC, it sends a message via message queue.
  * Clients receive messages, update their local ARP table, and fetch corresponding IP from shared memory.
* **Outcome:** Clients stay synchronized on ARP entries.
* **How to Test:** Add/remove ARP entry on server, watch all clients update automatically.

---

### Stage 4 – PID Tracking and Kill Signaling

**Objective:** Track clients and allow server to flush + signal.

* **Tasks:**

  * On sync completion, client sends PID to server.
  * Server stores PID in a list.
  * Server menu option: flush routing + ARP, then `kill(SIGUSR1, pid)` for each client.
  * Clients handle `SIGUSR1` by flushing their tables.
* **Outcome:** Server can control all clients with signals.
* **How to Test:** Run server + clients, add routes/ARP entries, choose “flush + kill,” see clients empty tables.

---

### Stage 5 – Clean Disconnect and Bye Protocol

**Objective:** Graceful termination.

* **Tasks:**

  * Client sends “BYE” before exiting.
  * Server removes client PID from its list.
  * Client clears its tables.
* **Outcome:** No stale PIDs, server reflects correct connected client count.
* **How to Test:** Start 3 clients, exit one, server shows only 2 active PIDs.

---

### Stage 6 – TCP Socket Upgrade

**Objective:** Replace Unix domain sockets with TCP sockets for remote use.

* **Tasks:**

  * Change server to bind to `127.0.0.1:PORT`.
  * Clients connect via TCP instead of Unix sockets.
  * Everything else (tables, sync logic, ARP) remains same.
* **Outcome:** Project can run across machines (e.g. your VPS).
* **How to Test:** Run server on VPS, connect clients locally and remotely.

---

## ✅ Additions (for realism and practice)

* Add **heartbeat messages** (every few seconds client sends ping, server removes unresponsive ones).
* Add **logging** with timestamps for both server and client.
* Add **config file** for server startup (initial routes, ARP entries).

---
